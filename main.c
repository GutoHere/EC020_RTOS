#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "oled.h"
#include "lightSensor.h"

/* The tasks to be created.  Two instances are created of the sender task while
only a single instance is created of the receiver task. */
static void vSendTask( void *pvParameters );
static void vReceiveTask( void *pvParameters );

/* Declare a variable of type xQueueHandle.  This is used to store the queue
that is accessed by all three tasks. */
xQueueHandle xQueue;

static uint32_t msTicks = 0;

void SysTick_Handler(void) {
    msTicks++;
}

static uint32_t getTicks(void)
{
    return msTicks;
}

int main (void)
{

	/* The queue is created to hold a maximum of 10 long values. */
	xQueue = xQueueCreate( 10, sizeof( uint32_t ) );

	newSensor();

	oledNew();

    if( xQueue != NULL )
    	{
    		/* Create two instances of the task that will write to the queue.  The
    		parameter is used to pass the value that the task should write to the queue,
    		so one task will continuously write 100 to the queue while the other task
    		will continuously write 200 to the queue.  Both tasks are created at
    		priority 1. */
    		xTaskCreate( vMandaTarefa, "Envia", 240, ( void * ) 100, 2, NULL );


    		/* Create the task that will read from the queue.  The task is created with
    		priority 2, so above the priority of the sender tasks. */
    		xTaskCreate( vRecebeTarefa, "Recebe", 240, NULL, 1, NULL );

    		/* Start the scheduler so the created tasks start executing. */
    		vTaskStartScheduler();
    	}
    	else
    	{
    		/* The queue could not be created. */
    	}

        /* If all is well we will never reach here as the scheduler will now be
        running the tasks.  If we do reach here then it is likely that there was
        insufficient heap memory available for a resource to be created. */
    	for( ;; );
    	return 0;

}

/*-----------------------------------------------------------*/

static void vSendTask( void *pvParameters )
{
long lValueToSend;
portBASE_TYPE xStatus;

	/* Two instances are created of this task so the value that is sent to the
	queue is passed in via the task parameter rather than be hard coded.  This way
	each instance can use a different value.  Cast the parameter to the required
	type. */
	lValueToSend = ( long ) pvParameters;
	int luz;


	/* As per most tasks, this task is implemented within an infinite loop. */
	for( ;; )
	{
		/* The first parameter is the queue to which data is being sent.  The
		queue was created before the scheduler was started, so before this task
		started to execute.

		The second parameter is the address of the data to be sent.

		The third parameter is the Block time � the time the task should be kept
		in the Blocked state to wait for space to become available on the queue
		should the queue already be full.  In this case we don�t specify a block
		time because there should always be space in the queue. */
		luz = sensorRead();
//		awake = TRUE;
		xStatus = xQueueSendToBack( xQueue, &luz, 100 );


		if( xStatus != pdPASS )
		{
			/* We could not write to the queue because it was full � this must
			be an error as the queue should never contain more than one item! */
			vPrintString( "Could not send to the queue.\r\n" );
		}
		else
		{
			vPrintString( "Mensagem enviada\r\n" );
		}

		/* Allow the other sender task to execute. */
		taskYIELD();
	}
}
/*-----------------------------------------------------------*/

static void vRecebeTarefa( void *pvParameters )
{
/* Declare the variable that will hold the values received from the queue. */
uint32_t lReceivedValue;
portBASE_TYPE xStatus;
const portTickType xTicksToWait = 100 / portTICK_RATE_MS;

	/* This task is also defined within an infinite loop. */
	for( ;; )
	{
		xStatus = xQueueReceive( xQueue, &lReceivedValue, xTicksToWait );

		if( xStatus == pdPASS )
		{
			/* Data was successfully received from the queue, print out the received
			value. */


			vPrintStringAndNumber( "Recebido = ", lReceivedValue );

			printOled(lReceivedValue);

		}
		else
		{
			/* We did not receive anything from the queue even after waiting for 100ms.
			This must be an error as the sending tasks are free running and will be
			continuously writing to the queue. */
			vPrintString( "Could not receive from the queue.\r\n" );
		}
	}
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}

void check_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while(1);
}
