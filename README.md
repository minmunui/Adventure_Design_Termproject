# Adventure_Design_Termproject
미션 알람시계를 제작한 아두이노 코드입니다.
해당 코드는 Atmega2560에서 작동되도록 작성했습니다.
## 기능
- 기본적인 시계의 기능 수행합니다.
- 알람설정, 시간설정을 할 수 있습니다.
- 알람을 끄기 위해서는 만보기를 작동시켜 일정 수치를 넘겨야만 합니다.
- 센서를 활용하기 위해 주변 온도를 표시하며 광도에 따라 아이콘이 변경됩니다.

## 주변장치
|번호|	상품코드|	품목|	상품명(옵션명)|	제조사|	링크|
|---|---|---|----|----|----|
|1|	1358495|	온습도센서	  |[SMG] DHT11 미니 온습도 센서모듈 [SZH-EK077]|	SMG	|https://www.devicemart.co.kr/goods/view?no=1358495
|2|	2733|   	피에조부저	  |[일오삼전자] IMT12D2001AP|	KEYES|	https://www.devicemart.co.kr/goods/view?no=2733
|3|	1384579|	LCD	      |[YwRobot] 2004 LCD I2C 디스플레이 모듈 블루 [DIS030002]|	YwRobot	|https://www.devicemart.co.kr/goods/view?no=1384579
|4|	1327438|	조도센서	  |[SMG-A] 아두이노 CdS 광/조도 센서 모듈 [SZH-SSBH-011]|	SMG-A|	https://www.devicemart.co.kr/goods/view?no=1327438
|5|	34405|	  아두이노보드|[Arduino] Arduino Mega 2560 (R3)|	Arduino	|https://www.devicemart.co.kr/goods/view?no=34405
|6|	15570|   	버튼	    |[KOREANA] KLT-1105AT|	KOREANA	|https://www.devicemart.co.kr/goods/view?no=15570
|7|	1383894|	진동센서	 |[YwRobot] 아두이노 진동센서 모듈 [SEN030201]	|YwRobot	|https://www.devicemart.co.kr/goods/view?no=1383894
|8|	2733|     부저	    |[일오삼전자] IMT12D2001AP|	일오삼전자	|https://www.devicemart.co.kr/goods/view?no=2733

## 라이브러리
- LiquidCrystal_I2C.h
- DHT.h
- DHT_U.h
- pitches.h
- TimeLib.h

## 장치연결

- 부저는 A1에 연결합니다.
- 진동센서는 11번 핀에 연결합니다.
- 풀다운 버튼을 2, 3, 4에 연결합니다.
- 조도센서는 A0에 연결합니다.
- LCD는 I2C 통신을 사용하므로 I2C통신선에 연결합니다.
