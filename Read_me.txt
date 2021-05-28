更新于2021/3/17
arduino-moveit：用ros里的程序控制机械臂的运动
	dual_ar2_moveit_arduino：12个电机运动，ros里读到走多少，传给机械臂多少

CUI_encoder:编码器的基础学习
	code_test:测试通过AB通道电平变化来读取编码器转数，反转也会往上记转数那种
	encoder_3_channel:测试通过ABX电平变化来读取编码器转数
	encoder_cw_ccw:和code_test一样，只是能分辨正反转了

motor:驱动步进电机的
	AR3_test:通过拉高拉低电平，从串口输入走多少步来实现电机转动
	arduino_test:串口输入多少步，用函数库实现走多少步
		文件夹里面的程序：6个电机
		文件夹外面的程序：1个电机
	arduino_test2:同上，5个电机
	J1：第一个关节的电机（10：1减速比的那个），走到多少再回来
	Motor_12_singlecontrol:12个电机，走到多少再回来（没法同时，要同时就要凑好）
	sketch_aug14a：测试一个电机电平拉高拉低走的那种
	sketch_aug14b：测试一个电机电平拉高拉低走快速慢速的
	sketch_aug14c：测试一个电机走到多少再回来
	stepper_contro：张师兄写的一个让它先加速再减速
	stepper_move：12个电机，走到多少再回来（没法同时，要同时就要凑好）
	stepper_move_control：stepper_move的测试程序（可修改）

motor_encoder:电机加编码器的
	encoer_polling：利用自己写的一个encoder_polling_v2.h来实现串口轮询打印一个编码器的状态
	multi_encoder：多个编码器的读取
		ar2_encoder_thread：用defineTaskLoop多线程函数来实现电机移动和编码器读取（发现编码器在多线程SCoop的函数库使用中，无论是否进行电机驱动这个线程，编码器会出现串口监视器中数据丢失的现象。 无论编码器反馈的数据读取在自己的线程loop中还是总的loop里。出现问题的原因未知。）
		ar2_no_input_with_encoder：数据不从串口监视器输入了，直接从电脑中给，用run（）函数来实现。目前还没有给出让机械臂能够自己回来的程序，机械臂只能在打开串口的时候一直往一个方向运动，编码器反馈的数据正常。
		encoder_function：电机自己动，用Encoder.h反馈编码器的值。一个。
		encoder_function_input：想要读取串口监视器中输入的数来驱动电机，驱动的同时串口监视器反馈编码器的位置信息。感觉不太可能
		encoder_function_SIX:单电机控制的方式，编码器读数也正常。 该程序待完善成六个电机的（需自己计算时间）。
		two_boards：两块板子，所以有两个程序，一个是给arduino的，另一个是给tennsy的，软串口通讯。

	stepper_encoder_J2：第二个关节电机自己过去又回来，编码器通过AB通道计数来打印位置
	stepper_encoder_one：第一个关节电机自己过去又回来，编码器通过AB通道计数来打印位置
	stepper_encoder_one_50：第一个关节电机自己过去又回来，编码器通过AB通道计数来打印角度
	stepper_encoder_one_interrupt：通过中断来实现编码器的读数
	stepper_encoder_oneadd：第一个关节电机自己过去又回来，编码器通过AB通道计数来打印位置，是测试用的
	sterpper_encoder_two：两个电机自己过去又回来，在串口监视器中反馈两个编码器的值（有问题）
	stepper_encoder_two_changeJ1：两个电机自己过去又回来，在串口监视器中反馈两个编码器的值（有问题）
	stepper_encoder_two_interrupt：两个电机自己过去又回来，利用中断读取编码器的值，在串口监视器中反馈两个编码器的值（有问题）
	stepper_encoder_two_string：两个电机自己过去又回来，在串口监视器中反馈两个编码器的值（有问题）

moveit_encoder：将编码器的值在ros中显示出来

Teensy:用teensy编写的读取编码器
	encoder_12：12个编码器在串口监视器中反馈
	encoder_test：两个编码器在串口监视器中反馈，测试用
	led_test：测试teensy的IO口的



