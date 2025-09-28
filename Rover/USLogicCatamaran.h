/*
 * USLogicCatamaran.h
 *
 *  Created on: Sep 25, 2025
 *      Author: Alex
 */

#pragma once
#include <RC_Channel/RC_Channel.h>
#include <SRV_Channel/SRV_Channel.h>
#include "AP_HAL/AP_HAL.h"
#include <GCS_MAVLink/GCS_MAVLink.h>
#include <AP_Relay/AP_Relay.h>

class US_Logic_Catamaran
{
public:
	US_Logic_Catamaran()
	{
	}
	const uint8_t rc_channel_right_starter = 3 - 1; // A button
	const uint8_t rc_channel_left_starter = 5 - 1; // D button
	const uint8_t rc_channel_right_left_podsos = 8 - 1; // B
	const uint8_t rc_channel_right_left_stop = 6 - 1; // E
	const uint8_t rc_channel_throttle = 3 - 1; // throttle
	const uint8_t rc_channel_transmission = 8 - 1; // C
	const uint8_t rc_channel_turn = 1 - 1; // C

	const uint8_t relay_channel_right_starter = 1 - 1;
	const uint8_t relay_channel_left_starter = 3 - 1;
	const uint8_t relay_channel_right_podsos = 2 - 1;
	const uint8_t relay_channel_left_podsos = 4 - 1;
	const uint8_t relay_channel_right_left_stop = 5 - 1;

	const uint8_t servo_channel_throttle = 12 - 1;
	const uint8_t servo_channel_transmission = 11 - 1;
	const uint8_t servo_channel_turn = 10 - 1;

	const uint16_t rc_on_value = 1700;
	const uint16_t rc_off_value = 1300;

	uint16_t rc_right_starter_value = 0;
	uint16_t rc_left_starter_value = 0;
	uint16_t rc_right_left_podsos_value = 0;
	uint16_t rc_throttle_value = 0;
	uint16_t rc_transmission_value = 0;
	uint16_t rc_turn_value = 0;
	uint16_t rc_right_left_stop_value = 0;

	const uint16_t rc_right_starter_failsafe_value = 1100;
	const uint16_t rc_left_starter_failsafe_value = 1100;
	const uint16_t rc_right_left_podsos_failsafe_value = 1500;
	const uint16_t rc_throttle_failsafe_value = 1100;
	const uint16_t rc_transmission_failsafe_value = 1100;
	const uint16_t rc_turn_failsafe_value = 1500;
	const uint16_t rc_right_left_stop_failsafe_value = 2000;

	bool stat = false;
	void update();
private:
	void relay_control();
	void servo_control();
};

