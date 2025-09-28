/*
 * USLogicCatamaran.cpp
 *
 *  Created on: Sep 25, 2025
 *      Author: Alex
 */

#include "USLogicCatamaran.h"
#include "Rover.h"

extern const AP_HAL::HAL &hal;

void US_Logic_Catamaran::update()
{

	static uint32_t last_ms = 0;
	uint32_t now = AP_HAL::millis();

	if (rc().has_valid_input() && !stat)
	{
		stat = true;
		GCS_SEND_TEXT(MAV_SEVERITY_INFO, "Зв'язок відновлено");
	} else if (!rc().has_valid_input() && stat)
	{
		stat = false;
		GCS_SEND_TEXT(MAV_SEVERITY_INFO, "Втрачено зв'язок");
	}

	if (stat)
	{
		rc_right_starter_value = rc().get_radio_in(rc_channel_right_starter);
		rc_left_starter_value = rc().get_radio_in(rc_channel_left_starter);
		rc_right_left_podsos_value = rc().get_radio_in(
				rc_channel_right_left_podsos);
		rc_right_left_stop_value = rc().get_radio_in(
				rc_channel_right_left_stop);
		rc_throttle_value = rc().get_radio_in(rc_channel_throttle);
		rc_transmission_value = rc().get_radio_in(rc_channel_transmission);
		rc_turn_value = rc().get_radio_in(rc_channel_turn);
	} else
	{ // failsafe set
		rc_right_starter_value = rc_right_starter_failsafe_value;
		rc_left_starter_value = rc_left_starter_failsafe_value;
		rc_right_left_podsos_value = rc_right_left_podsos_failsafe_value;
		rc_right_left_stop_value = rc_right_left_stop_failsafe_value;
		rc_throttle_value = rc_throttle_failsafe_value;
		rc_transmission_value = rc_transmission_failsafe_value;
		rc_turn_value = rc_turn_failsafe_value;
	}
	if (now > last_ms + 50)
	{
		last_ms = now;
		relay_control();
		servo_control();
	}

}
void US_Logic_Catamaran::servo_control()
{
	SRV_Channels::set_output_pwm_chan(servo_channel_throttle,
			rc_throttle_value);
	SRV_Channels::set_output_pwm_chan(servo_channel_transmission,
			rc_transmission_value);
	SRV_Channels::set_output_pwm_chan(servo_channel_turn, rc_turn_value);
}
void US_Logic_Catamaran::relay_control()
{

	if (rc_right_starter_value > rc_on_value)
	{
		AP::relay()->on(relay_channel_right_starter);
	} else if (rc_right_starter_value < rc_off_value)
	{
		AP::relay()->off(relay_channel_right_starter);
	}

	if (rc_left_starter_value > rc_on_value)
	{
		AP::relay()->on(relay_channel_left_starter);
	} else if (rc_left_starter_value < rc_off_value)
	{
		AP::relay()->off(relay_channel_left_starter);
	}
	if (rc_right_left_podsos_value > rc_on_value)
	{
		AP::relay()->on(relay_channel_right_podsos);
		AP::relay()->off(relay_channel_left_podsos);
	} else if (rc_right_left_podsos_value < rc_off_value)
	{
		AP::relay()->off(relay_channel_right_podsos);
		AP::relay()->on(relay_channel_left_podsos);
	} else
	{
		AP::relay()->off(relay_channel_right_podsos);
		AP::relay()->off(relay_channel_left_podsos);
	}
	if (rc_right_left_stop_value > rc_on_value)
	{
		AP::relay()->on(relay_channel_right_left_stop);
	} else if (rc_right_left_stop_value < rc_off_value)
	{
		AP::relay()->off(relay_channel_right_left_stop);
	}
}
