/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ADC2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t readValue;
uint16_t readValue2;

void sendMessageFromISRWithNewLine(std::string x) {
	x += "\n";
	HAL_UART_Transmit(&huart1, (uint8_t*) x.c_str(), x.size(), 10);
}

void sendMessageFromISRWithNewLine(uint16_t x) {

	std::string string_msg = std::to_string(x);
	string_msg += "\n";
	HAL_UART_Transmit(&huart1, (uint8_t*) string_msg.c_str(), string_msg.size(),
			10);

}

uint16_t i = 0, AD_RES[4];
ADC_ChannelConfTypeDef ADC_CH_Cfg = { 0 };
uint32_t ADC_Channels[3] = { ADC_CHANNEL_2, ADC_CHANNEL_3, ADC_CHANNEL_4 };

//
//characters.push_back(Character("esc", "0000"));
//characters.push_back(Character("f1", "0001"));
//characters.push_back(Character("f2", "0002"));
//characters.push_back(Character("f3", "0010"));
//characters.push_back(Character("f4", "0011"));
//characters.push_back(Character("f5", "0012"));
//characters.push_back(Character("f6", "0020"));
//characters.push_back(Character("f7", "0021"));
//characters.push_back(Character("f8", "0022"));
//characters.push_back(Character("f9", "0100"));
//characters.push_back(Character("f10", "0101"));
//characters.push_back(Character("f11", "0102"));
//
//characters.push_back(Character("f12", "0110"));
//characters.push_back(Character("PrScr", "0111"));
//characters.push_back(Character("delete", "0112"));
//characters.push_back(Character("~", "0120"));
//characters.push_back(Character("1", "0121"));
//characters.push_back(Character("2", "0122"));
//characters.push_back(Character("3", "0200"));
//characters.push_back(Character("4", "0201"));
//characters.push_back(Character("5", "0202"));
//characters.push_back(Character("6", "0210"));
//characters.push_back(Character("7", "0211"));
//characters.push_back(Character("8", "0212"));
//characters.push_back(Character("9", "0220"));
//characters.push_back(Character("0", "0221"));
//
//characters.push_back(Character("-_", "0222"));
//characters.push_back(Character("plus=", "1000"));
//characters.push_back(Character("backspace", "1001"));
//characters.push_back(Character("tab", "1002"));
//characters.push_back(Character("q", "1010"));
//characters.push_back(Character("w", "1011"));
//characters.push_back(Character("e", "1012"));
//characters.push_back(Character("r", "1020"));
//characters.push_back(Character("t", "1021"));
//characters.push_back(Character("y", "1022"));
//characters.push_back(Character("u", "1100"));
//characters.push_back(Character("i", "1101"));
//characters.push_back(Character("o", "1102"));
//characters.push_back(Character("p", "1110"));
//
//characters.push_back(Character("{", "1111"));
//characters.push_back(Character("}", "1112"));
//characters.push_back(Character("| \\ /", "1120"));
//characters.push_back(Character("caps", "1121"));
//characters.push_back(Character("a", "1122"));
//characters.push_back(Character("s", "1200"));
//characters.push_back(Character("d", "1201"));
//characters.push_back(Character("f", "1202"));
//characters.push_back(Character("g", "1210"));
//characters.push_back(Character("h", "1211"));
//characters.push_back(Character("j", "1212"));
//characters.push_back(Character("k", "1220"));
//characters.push_back(Character("l", "1221"));
//characters.push_back(Character(":;", "1222"));
//
//characters.push_back(Character("\" \'", "2000"));
//characters.push_back(Character("enter", "2001"));
//characters.push_back(Character("shift", "2002"));
//characters.push_back(Character("z", "2010"));
//characters.push_back(Character("x", "2011"));
//characters.push_back(Character("c", "2012"));
//characters.push_back(Character("v", "2020"));
//characters.push_back(Character("b", "2021"));
//characters.push_back(Character("n", "2022"));
//characters.push_back(Character("m", "2100"));
//characters.push_back(Character("<,", "2101"));
//characters.push_back(Character(">.", "2102"));
//characters.push_back(Character("?/", "2110"));
//characters.push_back(Character("ctrl", "2111"));
//
//characters.push_back(Character("fn", "2112"));
//characters.push_back(Character("win", "2120"));
//characters.push_back(Character("alt", "2121"));
//characters.push_back(Character("space", "2122"));

std::map<std::string, std::string> codeAndCharReversed { { "esc", "0000" }, {
		"f1", "0001" }, { "f2", "0002" }, { "f3", "0010" }, { "f4", "0011" }, {
		"f5", "0012" }, { "f6", "0020" }, { "f7", "0021" }, { "f8", "0022" }, {
		"f9", "0100" }, { "f10", "0101" }, { "f11", "0102" }, { "f12", "0110" },
		{ "PrScr", "0111" }, { "delete", "0112" }, { "~", "0120" }, { "1",
				"0121" }, { "2", "0122" }, { "3", "0200" }, { "4", "0201" }, {
				"5", "0202" }, { "6", "0210" }, { "7", "0211" },
		{ "8", "0212" }, { "9", "0220" }, { "0", "0221" }, { "-_", "0222" }, {
				"plus=", "1000" }, { "backspace", "1001" }, { "tab", "1002" }, {
				"q", "1010" }, { "w", "1011" }, { "e", "1012" },
		{ "r", "1020" }, { "t", "1021" }, { "y", "1022" }, { "u", "1100" }, {
				"i", "1101" }, { "o", "1102" }, { "p", "1110" },
		{ "{", "1111" }, { "}", "1112" }, { "| \\ /", "1120" },
		{ "caps", "1121" }, { "a", "1122" }, { "s", "1200" }, { "d", "1201" }, {
				"f", "1202" }, { "g", "1210" }, { "h", "1211" },
		{ "j", "1212" }, { "k", "1220" }, { "l", "1221" }, { ":;", "1222" }, {
				"\" \'", "2000" }, { "enter", "2001" }, { "shift", "2002" }, {
				"z", "2010" }, { "x", "2011" }, { "c", "2012" },
		{ "v", "2020" }, { "b", "2021" }, { "n", "2022" }, { "m", "2100" }, {
				"<,", "2101" }, { ">.", "2102" }, { "?/", "2110" }, { "ctrl",
				"2111" }, { "fn", "2112" }, { "win", "2120" },
		{ "alt", "2121" }, { "space", "2122" } };

std::map<std::string, std::string> codeAndChar;

class Borders {
public:
	int state;
	int one, two, three, four;

	Borders(int one, int two, int three, int four) {
		this->one = one;
		this->two = two;
		this->three = three;
		this->four = four;
	}
	;

	void setState(int curValue) {
		if (curValue >= one && curValue <= two) {
			state = 0;
		} else if (curValue > two && curValue <= three) {
			state = 1;
		} else if (curValue > three && curValue <= four) {
			state = 2;
		}
	}
	int getState() {
		return state;
	}
};

std::vector<Borders> borders;

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_ADC1_Init();
	MX_USART1_UART_Init();
	MX_ADC2_Init();
	/* USER CODE BEGIN 2 */
	HAL_ADC_Start(&hadc1);
	HAL_ADC_Start(&hadc2);

	ADC_CH_Cfg.Rank = ADC_REGULAR_RANK_1;
	ADC_CH_Cfg.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
//700 1200 1500 500-900 900-1300 1300-1700
//700 1500 2100 500-1200 1200-1800 1800-2300
//900 1500 2100 500-1200 1200-1800 1800-2300
//900 1500 2100 500-1200 1200-1800 1800-2300

	borders.push_back(Borders(500, 900, 1150, 1700));
	borders.push_back(Borders(500, 1200, 1800, 2300));
	borders.push_back(Borders(500, 1200, 1800, 2300));
	borders.push_back(Borders(500, 1200, 1800, 2300));

	for (const auto &pair : codeAndCharReversed) {
		codeAndChar[pair.second] = pair.first;
	}

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		for (i = 0; i < 3; i++) {

			ADC_CH_Cfg.Channel = ADC_Channels[i];  // Select The ADC Channel [i]
			HAL_ADC_ConfigChannel(&hadc2, &ADC_CH_Cfg); // Configure The Selected ADC Channel
			HAL_ADC_Start(&hadc2);    // Start ADC Conversion @ Selected Channel
			HAL_ADC_PollForConversion(&hadc2, 1); // Poll The ADC Channel With TimeOut = 1mSec

			if (i == 0)
				AD_RES[1] = HAL_ADC_GetValue(&hadc2); // Read The ADC Conversion Result
			else if (i == 1)
				AD_RES[3] = HAL_ADC_GetValue(&hadc2); // Read The ADC Conversion Result
			else if (i == 2)
				AD_RES[0] = HAL_ADC_GetValue(&hadc2); // Read The ADC Conversion Result
		}

		HAL_ADC_PollForConversion(&hadc1, 1000);
//	  readValue = HAL_ADC_GetValue(&hadc1);

		AD_RES[2] = HAL_ADC_GetValue(&hadc1);

		static bool shouldReadTwoCharPressed = 0;
		static bool shouldReadOneChar = 0;

		// If Touch is Detected
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10)) {
			shouldReadTwoCharPressed = 1;
		} else {
			shouldReadTwoCharPressed = 0;
		}

		// If Touch is Detected
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11)) {
			shouldReadOneChar = 1;
		} else {
			shouldReadOneChar = 0;
		}

		static bool wasReadingMultipleCharsStarted = 0;
		static std::map<std::string, std::string> multipleCharsToSendMap;
		static std::string multipleCharsToSendString;
		static std::string currentChar;
		static std::vector<std::string> insertion_order_keys;
		static bool shouldShowDebug = false;
		// is
		static int counterOfReadTwoChar = 0;
		static int counterOfReadOneChar = 0;

		if (shouldReadTwoCharPressed == 1)
			counterOfReadTwoChar++;
		else {
			// if button was unpressed
			counterOfReadTwoChar = 0;
		}

		// button was pressed just now
		if (counterOfReadTwoChar == 1) {
			// ends of reading multiple chars because button was already pressed before = second time button was pressed
			if (wasReadingMultipleCharsStarted == 1) {
				wasReadingMultipleCharsStarted = 0;
				if (multipleCharsToSendMap.empty())
					continue;


				multipleCharsToSendString = "";
				for (const auto &pair : insertion_order_keys) {
					sendMessageFromISRWithNewLine(multipleCharsToSendMap[pair]);
					multipleCharsToSendString += multipleCharsToSendMap[pair];
				}

				//send finished chars
				sendMessageFromISRWithNewLine("chars as single sttring="+multipleCharsToSendString);

				multipleCharsToSendString = "";
				multipleCharsToSendMap.clear();
				insertion_order_keys.clear();
			} else {
				// starts reading multiple chars
				wasReadingMultipleCharsStarted = 1;
			}
		}

		sendMessageFromISRWithNewLine("map vals=");

		for (const auto &pair : insertion_order_keys) {
			sendMessageFromISRWithNewLine(multipleCharsToSendMap[pair]);
		}

		if (shouldShowDebug) {

			for (const auto &pair : insertion_order_keys) {
				multipleCharsToSendString += multipleCharsToSendMap[pair];
			}

			sendMessageFromISRWithNewLine("current multipleCharsToSend=");
			sendMessageFromISRWithNewLine(multipleCharsToSendString);
			multipleCharsToSendString = "";
		}

		if (shouldShowDebug) {
			sendMessageFromISRWithNewLine("fingers vals=");
			sendMessageFromISRWithNewLine(AD_RES[0]);
			sendMessageFromISRWithNewLine(AD_RES[1]);
			sendMessageFromISRWithNewLine(AD_RES[2]);
			sendMessageFromISRWithNewLine(AD_RES[3]);
		}


		for (int i = 0; i < borders.size(); i++) {
			borders.at(i).setState(AD_RES[i]);
//			sendMessageFromISRWithNewLine(borders.at(i).getState());
		}

		//states as single string + send
		std::string statesString = std::to_string(borders.at(0).getState())
				+ std::to_string(borders.at(1).getState())
				+ std::to_string(borders.at(2).getState())
				+ std::to_string(borders.at(3).getState()); // Convert int to string
		sendMessageFromISRWithNewLine("fingers states="+statesString);

		if (shouldReadOneChar) {
			counterOfReadOneChar++;
		} else {
			counterOfReadOneChar = 0;
		}

		// if button was pressed change curChar + send it + connect to multiCharIf corresponding button was pressed
		if (counterOfReadOneChar == 1) {
			currentChar = codeAndChar[statesString];

			if (shouldShowDebug) {
				// send char
				if (shouldReadOneChar) {

					sendMessageFromISRWithNewLine("new char was read="+currentChar);

				}
			}

			// add a new char to a multipleChar map
			if (wasReadingMultipleCharsStarted) {

				// if there is no such elem
				if (multipleCharsToSendMap.find(statesString)
						== multipleCharsToSendMap.end()) {

					insertion_order_keys.push_back(statesString);
					multipleCharsToSendMap[statesString] =
							codeAndChar[statesString];

					sendMessageFromISRWithNewLine(
							"Newval added"
									+ multipleCharsToSendMap[statesString]);
				}
			}
		}

		sendMessageFromISRWithNewLine("current char="+codeAndChar[statesString]);

		if (shouldShowDebug) {
			sendMessageFromISRWithNewLine("buttons="+std::to_string(shouldReadOneChar)+std::to_string(shouldReadTwoCharPressed));
		}
//	  int a = 10;
//	  char *intStr = itoa(readValue);
//	  std::string str = std::string(intStr);
//
//	  std::string string_msg = std::to_string(readValue);
//	  sendMessageFromISRWithNewLine(readValue);

//	  HAL_UART_Transmit(&huart1, (uint8_t*)"Ni Hao \n", strlen("Ni Hao \n"), 100);
//	  printf("qwe rty \n");
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(200);
		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}

	/** Enables the Clock Security System
	 */
	HAL_RCC_EnableCSS();
}

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC1_Init(void) {

	/* USER CODE BEGIN ADC1_Init 0 */

	/* USER CODE END ADC1_Init 0 */

	ADC_ChannelConfTypeDef sConfig = { 0 };

	/* USER CODE BEGIN ADC1_Init 1 */

	/* USER CODE END ADC1_Init 1 */

	/** Common config
	 */
	hadc1.Instance = ADC1;
	hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc1.Init.ContinuousConvMode = ENABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	if (HAL_ADC_Init(&hadc1) != HAL_OK) {
		Error_Handler();
	}

	/** Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_9;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN ADC1_Init 2 */

	/* USER CODE END ADC1_Init 2 */

}

/**
 * @brief ADC2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC2_Init(void) {

	/* USER CODE BEGIN ADC2_Init 0 */

	/* USER CODE END ADC2_Init 0 */

	ADC_ChannelConfTypeDef sConfig = { 0 };

	/* USER CODE BEGIN ADC2_Init 1 */

	/* USER CODE END ADC2_Init 1 */

	/** Common config
	 */
	hadc2.Instance = ADC2;
	hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc2.Init.ContinuousConvMode = ENABLE;
	hadc2.Init.DiscontinuousConvMode = DISABLE;
	hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc2.Init.NbrOfConversion = 1;
	if (HAL_ADC_Init(&hadc2) != HAL_OK) {
		Error_Handler();
	}

	/** Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_2;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN ADC2_Init 2 */

	/* USER CODE END ADC2_Init 2 */

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */

	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(Qwerty_GPIO_Port, Qwerty_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : Qwerty_Pin */
	GPIO_InitStruct.Pin = Qwerty_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(Qwerty_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : PB10 PB11 */
	GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
