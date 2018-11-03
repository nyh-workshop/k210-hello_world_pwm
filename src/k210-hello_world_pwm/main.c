/* Copyright 2018 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <devices.h>
#include <stdio.h>
#include <pin_cfg.h>

// K210 Dock:
// IO_12 = Blue LED
// IO_13 = green LED
// IO_14 = red LED
// 1.0 is 0% duty cycle, 0.0 is 100% duty cycle.

const fpioa_cfg_t g_fpioa_cfg =
{
    .version = PIN_CFG_VERSION,
    .functions_count = 3,
    .functions =
    {
        {12, FUNC_TIMER0_TOGGLE1}, // Channel 0
		{13, FUNC_TIMER0_TOGGLE2}, // Channel 1
	    {14, FUNC_TIMER0_TOGGLE3}  // Channel 2
    }
};

#define CHANNEL0 0
#define CHANNEL1 1
#define CHANNEL2 2

uintptr_t gio;
uintptr_t pwm0;
uintptr_t pwm1;
uintptr_t timer;

void irq_time(void *userdata)
{
    static double cnt = 0.01;
    static int flag = 0;
    pwm_set_enable(pwm0, CHANNEL0, 0);
	pwm_set_enable(pwm0, CHANNEL1, 0);
	//pwm_set_enable(pwm0, CHANNEL2, 0);
    pwm_set_active_duty_cycle_percentage(pwm0, CHANNEL0, cnt);
	pwm_set_active_duty_cycle_percentage(pwm0, CHANNEL1, 1.0-cnt);
	//pwm_set_active_duty_cycle_percentage(pwm0, CHANNEL2, 1);
    pwm_set_enable(pwm0, CHANNEL0, 1);
	pwm_set_enable(pwm0, CHANNEL1, 1);
	//pwm_set_enable(pwm0, CHANNEL2, 1);
    flag ? (cnt -= 0.01) : (cnt += 0.01);
    if (cnt > 1.0)
    {
        cnt = 1.0;
        flag = 1;
    }
    else if (cnt < 0.0)
    {
        cnt = 0.0;
        flag = 0;
    }
}

int main()
{
    pwm0 = io_open("/dev/pwm0");
    configASSERT(pwm0);
    pwm_set_frequency(pwm0, 1000); //set 1000HZ
    pwm_set_active_duty_cycle_percentage(pwm0, CHANNEL0, 1.0); //duty  0%
	pwm_set_active_duty_cycle_percentage(pwm0, CHANNEL1, 1.0); //duty  0%
	pwm_set_active_duty_cycle_percentage(pwm0, CHANNEL2, 1.0); //duty  0%
    pwm_set_enable(pwm0, CHANNEL0, 1);
	pwm_set_enable(pwm0, CHANNEL1, 1);
	pwm_set_enable(pwm0, CHANNEL2, 1);

    timer = io_open("/dev/timer10");
    configASSERT(timer);

    timer_set_interval(timer, 1e7);
    timer_set_on_tick(timer, irq_time, NULL);
    timer_set_enable(timer, 1);

    while (1)
        ;
}