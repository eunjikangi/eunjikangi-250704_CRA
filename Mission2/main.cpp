#ifdef _DEBUG
#include "gmock/gmock.h"
int main()
{
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CarClient.h"

void delay(int ms)
{
	volatile int sum = 0;
	for (int i = 0; i < 1000; i++)
		for (int j = 0; j < 1000; j++)
			for (int t = 0; t < ms; t++)
				sum++;
}

int main()
{
	char buf[100];
	CarClient client;

	while (1)
	{
		client.printStepUI();

		fgets(buf, sizeof(buf), stdin);
		char* context = nullptr;
		strtok_s(buf, "\r", &context);
		strtok_s(buf, "\n", &context);
		if (!strcmp(buf, "exit")) {
			printf("바이바이\n");
			break;
		}
		
		char* checkNumber;
		int answer = strtol(buf, &checkNumber, 10);
		if (*checkNumber != '\0') {
			printf("ERROR :: 숫자만 입력 가능\n");
			delay(800);
			continue;
		}
		
		if (!client.isInputValid(answer)) {
			delay(800);
			continue;
		}
		
		client.processAnswer(answer);
		delay(800);
	}
}
#endif