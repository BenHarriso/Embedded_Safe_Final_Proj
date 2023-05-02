#include <msp430.h> 


/**
 * main.c
 */
//Brian Scala, Ben Harrison, Brandon Tran
//Final Project Code



unsigned int a=0;
unsigned int b=0;
unsigned int c=0;
unsigned int d=0;
unsigned int enter=0;
unsigned int Button_counter=0;
#define RED_LED BIT2
#define GREEN_LED BIT3
#define BLUE_LED BIT4

//unsigned int arr[4];
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	gpioInit();

	  TB0CTL = TBSSEL_2 + MC_1 + ID_3; // Timer A0: SMCLK, up mode, div by 8
	  TB0CCR0 = 62500; // 0.5s period (assuming SMCLK = 1MHz and ID = 8)
	  TB0CCTL0 = CCIE; // Enable interrupt

	    // Configure Timer_A
	    TA0CTL = TBSSEL__SMCLK | MC__UP | TBIE;              // SMCLK, UP mode
	    TA0CCTL2 |= CCIE;                                    // Enable TB0 CCR1 Interrupt
	    TA0CCR0 = 20000;                                      // Set CCR0 to the value to set the period
	    TA0CCR1 = 18500;                                       // Set CCR1 to the Duty Cycle


	    __bis_SR_register(LPM3_bits | GIE);           // Enter LPM3, enable interrupts


	    __no_operation();                             // For debugger
	  __enable_interrupt(); // Enable global interrupts

	while(1){

	}

}
#pragma vector=PORT2_VECTOR
__interrupt void Port_4(void)
{
    P4IFG &= ~BIT0;      // Clear P4.0 IFG


     Button_counter++;
   if(Button_counter == 0) {
        a = 0;  // Set first digit to 0
        Button_counter++; // Go to next digit
    }
    else if (Button_counter == 1){
        b = 0; // Set second digit to 0
        Button_counter++;
    }
    else if (Button_counter == 2) {
        c = 0; // Set third digit to 0
        Button_counter++;
    }
        else if (Button_counter == 3)
        {
            d = 0; //Set four digit to 0
            Button_counter++;
        }

}

#pragma vector=PORT4_VECTOR
__interrupt void Port_5(void)
{
    P5IFG &= ~BIT0;    // Clear P5.0 IFG
    P5IFG &= ~BIT1;    // Clear P5.1 IFG
    P5IFG &= ~BIT2;    // Clear P5.2 IFG
    P5IFG &= ~BIT3;    // Clear P5.3 IFG
    P5IFG &= ~BIT4;    // Clear P5.4 IFG

     Button_counter++;
   if(Button_counter == 0 && (P5IN & BIT0)) {
        a = 1;  // Set first digit to 1
        Button_counter++; // Go to next digit
    }
    else if (Button_counter == 1 && (P5IN & BIT0)){
        b = 1; // Set second digit to 1
        Button_counter++;
    }
    else if (Button_counter == 2 && (P5IN & BIT0)) {
        c = 1; // Set third digit to 1
        Button_counter++;
    }
        else if (Button_counter == 3 && (P5IN & BIT0))
        {
            d = 1; //Set four digit to 1

        }
        if(Button_counter == 0 && (P5IN & BIT1)) {
        a = 2;  // Set first digit to 1
        Button_counter++; // Go to next digit
    }
    else if (Button_counter == 1 && (P5IN & BIT1)){
        b = 2; // Set second digit to 1
        Button_counter++;
    }
    else if (Button_counter == 2 && (P5IN & BIT1)) {
        c = 2; // Set third digit to 1
        Button_counter++;
    }
        else if (Button_counter == 3 && (P5IN & BIT1))
        {
            d = 2; //Set four digit to 1

        }


        if(Button_counter == 0 && (P5IN & BIT2)) {
             a = 3;  // Set first digit to 1
             Button_counter++; // Go to next digit
         }
         else if (Button_counter == 1 && (P5IN & BIT2)){
             b = 3; // Set second digit to 1
             Button_counter++;
         }
         else if (Button_counter == 2 && (P5IN & BIT2)) {
             c = 3; // Set third digit to 1
             Button_counter++;
         }
             else if (Button_counter == 3 && (P5IN & BIT2))
             {
                 d = 3; //Set four digit to 1

             }

        if(Button_counter == 0 && (P5IN & BIT3)) {
             a = 0;  // Set first digit to 1
             b=0;
             c=0;
             d=4;
             Button_counter=0; // Go to next digit

         }

        if(Button_counter == 0 && (P5IN & BIT4)) {
            int lock = 0;
             enter = 1;  // Set first digit to 1
             if(a==1&&b==2&&c==3&&d==0)
             {
                 TA0CCR1 += 1000; //Unlock Safe
                 a = 1;
             }
             if(a == 1)
             {
                 TA0CCR1 -= 1000; //Lock Safe
                 a=0;
             }
        }




}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)
{



  if (enter&(a==1&&b==2&&c==3&&d==0))
  {
      P6OUT &= ~RED_LED;
      P6OUT |= GREEN_LED;
  }
  else
  {
    P6OUT |= RED_LED;
    P6OUT &= ~GREEN_LED;
  }

}

void gpioInit()
{

    P4IN |= BIT0;                          // Configure P4.0 as pulled-up
    P4REN |= BIT1;                          // P4.0 pull-up register enable
    P4IES |= BIT1;                         // P4.0 Low --> High edge
    P4IE |= BIT1;                          //P4.0 Interrupt Enable




    P5OUT |= BIT0;                          // Configure P5.0 as pulled-up
    P5REN |= BIT0;                          // 5.0 pull-up register enable
    P5IES |= BIT0;                         // P5.0 Low --> High edge
    P5IE |= BIT0;                               //P5.0 Interrupt Enable


    P5OUT |= BIT1;                          // Configure P5.1 as pulled-up
    P5REN |= BIT1;                          // 5.1 pull-up register enable
    P5IES |= BIT1;                         // P5.1 Low --> High edge
    P5IE |= BIT1;                               //P5.1 Interrupt Enable

    P5OUT |= BIT2;                          // Configure P5.2 as pulled-up
    P5REN |= BIT2;                          // 5.2 pull-up register enable
    P5IES |= BIT2;                         // P5.2 Low --> High edge
    P5IE |= BIT2;                               //P5.2 Interrupt Enable

    P5OUT |= BIT3;                          // Configure P5.3 as pulled-up
    P5REN |= BIT3;                          // 5.3 pull-up register enable
    P5IES |= BIT3;                         // P5.3 Low --> High edge
    P5IE |= BIT3;                               //P5.3 Interrupt Enable

    P5OUT |= BIT4;                          // Configure P5.4 as pulled-up
    P5REN |= BIT4;                          // 5.4 pull-up register enable
    P5IES |= BIT4;                         // P5.4 Low --> High edge
    P5IE |= BIT4;                               //P5.4 Interrupt Enable


    P6DIR |= BIT0;                          // Set P6.0 to output direction
    P6OUT &= ~BIT0;                         // Clear P6.0 output latch for a defined power-on state


    P6DIR |= RED_LED + GREEN_LED + BLUE_LED; // Set pins as output
    P6OUT &= ~(RED_LED + GREEN_LED + BLUE_LED); // Turn off all LEDs
}

__interrupt void TIMER0_A1_ISR(void)
void __attribute__ ((interrupt(TIMER0_B1_VECTOR))) TIMER0_A1_ISR (void)
{
    switch(__even_in_range(TB0IV,TB0IV_TBIFG))
    {
        case TA0IV_NONE:
            break;                               // No interrupt
        case TA0IV_TBCCR1:
            if(TA0CCR1){
            P6OUT |= BIT0;                       // overflow Set the pin to a 1
            }
            break;
        case TA0IV_TBCCR2:

            break;
        case TA0IV_TBIFG:
            P6OUT &= ~BIT0;                      // CCR1 Set the pin to a 0

            break;
        default:
            break;
    }
}






