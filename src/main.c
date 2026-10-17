#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <dk_buttons_and_leds.h>

LOG_MODULE_REGISTER(Lesson4_Exercise2, LOG_LEVEL_INF);

/* STEP 5.4 - Retrieve the device structure for the servo motor */
#define SERVO_MOTOR     DT_NODELABEL(servo) 
static const struct pwm_dt_spec pwm_servo = PWM_DT_SPEC_GET(SERVO_MOTOR);

/* STEP 5.5 - Use DT_PROP() to obtain the minimum and maximum duty cycle */
//#define PWM_SERVO_MIN_PULSE_WIDTH    DT_PROP(SERVO_MOTOR, min_pulse)
//#define PWM_SERVO_MAX_PULSE_WIDTH    DT_PROP(SERVO_MOTOR, max_pulse)

void button_handler(uint32_t button_state, uint32_t has_changed)
{
    int err = 0;
	if (has_changed & button_state)
	{
		switch (has_changed)
		{
            /* STEP 2.4 - Change motor angle when a button is pressed */
            /* STEP 5.6 - Update the button handler with the new duty cycle */
            /*case DK_BTN1_MSK:
                LOG_INF("Button 1 pressed");
                err = pwm_set_dt(&pwm_servo, PWM_MSEC(20), PWM_USEC(400));
                break;
            case DK_BTN2_MSK:
                LOG_INF("Button 2 pressed");
                err = pwm_set_dt(&pwm_servo, PWM_MSEC(20), PWM_USEC(1600));
                break;
            case DK_BTN3_MSK:
                LOG_INF("Button 3 pressed");
                err = pwm_set_dt(&pwm_servo, PWM_MSEC(20), PWM_USEC(2400));
                break;*/

            case DK_BTN1_MSK:
                // 180 degrees
                LOG_INF("Button 1 pressed");
                pwm_set_dt(&pwm_servo, PWM_MSEC(20), PWM_USEC(0.5*1000));
                break;
            case DK_BTN2_MSK:
                // 90 degrees
                LOG_INF("Button 2 pressed");
                pwm_set_dt(&pwm_servo, PWM_MSEC(20), PWM_USEC(1.5*1000));
                break;
            case DK_BTN3_MSK:
                // 0 degrees
                LOG_INF("Button 3 pressed");
                pwm_set_dt(&pwm_servo, PWM_MSEC(20), PWM_USEC(2.5*1000));
                break;

            case DK_BTN4_MSK:
                LOG_INF("Button 4 pressed");
                for(double i=0.5; i<=2.5; i+=0.1){
                    pwm_set_dt(&pwm_servo, PWM_MSEC(20), PWM_USEC(i*1000));
                    k_msleep(500);
                }
                pwm_set_dt(&pwm_servo, PWM_MSEC(20), PWM_USEC(2.5*1000));
                break;
			default:
				break;
		}
        if (err) {
            LOG_ERR("Error: couldn't set duty cycle, err %d", err);
        }
	}
}

int main(void)
{

    int err = 0;
        
    if (dk_buttons_init(button_handler)) {
        LOG_ERR("Failed to initialize the buttons library");
    }

    /* STEP 5.7 - Check if the motor device is ready and set its initial value */
    LOG_INF("Setting initial motor");
    if (!pwm_is_ready_dt(&pwm_servo)) {
        LOG_ERR("Error: PWM device %s is not ready", pwm_servo.dev->name);
        return 0;
	}

    return 0;
}
