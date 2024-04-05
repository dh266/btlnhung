# btl



REPORT


THIẾT KẾ VÀ THỰC HIỆN HỆ THỐNG ĐẾM SỐ BƯỚC CHÂN
Design and Implementation of a Pedometer 
Ver 0.2
19/04/2023

Tóm tắt (Abstract - from 5 to 10 lines)
Dự án này thiết kế và thực thi một bộ đếm số bước chân, sử dụng cảm biến gia tốc và các ngoại vi có sẵn trên bo mạch FRDM-KL46z. Hệ thống sẽ đếm số bước chân khi người sử dụng di chuyển và hiển thị kết quả lên màn hình LCD. Ngoài ra, hệ thống có các chức năng như chuyển đổi trạng thái hoạt động và dừng bằng nút bấm, reset kết quả đếm và hiển thị trạng thái qua LED. Một timer được sử dụng để điều chỉnh tần số nhấp nháy của LED xanh. Dự án yêu cầu cấu hình phù hợp của các thành phần và giao tiếp giữa chúng để hoạt động chính xác. 




Từ khóa (Keywords)

Hướng dẫn (Guide)

Document History
Version	Time	Revised by	Description
V0.1	15/4/2023	Nguyễn Kiêm Hùng	Original Version
V0.2	1904/2023	Nguyễn Kiêm Hùng	Modified the format of report
			
 

Mục lục (Table of Contents)

Document History	3
Table of Contents	4
1.	Giới thiệu (Introduction)	6
2.	Yêu cầu đối với thiết kế (Requirements)	6
2.1.	Yêu cầu đối với thiết kế	6
2.2.	Đặc tả kỹ thuật (Specification)	7
3.	Thực hiện hệ thống (Implementation)	7
3.1.	Kiến trúc phần cứng (Hardware Architecture)	7
3.1.1.	Khối xử lý trung tâm	8
3.1.2.	Cảm biến đầu vào	8
3.1.3.	Các LED	8
3.1.4.	LCD	8
3.2.	Lập trình phần mềm	8
3.2.1.	Thiết lập Clock cho hệ thống	8
3.2.2.	Khởi tạo các LED	9
3.2.3.	Khởi tạo các Switch	9
3.2.4.	Khởi tạo Systick Timer	9
3.2.5.	Thiết lập mức ưu tiên cho các ngắt	9
3.2.6.	Chương trình điều khiển (Hàm main())	9
4.	Kiểm chứng (Validation)	9
5.	Kết luận (Conclusion)	9
Appendix A: Schematic	10
Appendix B: Code	11
Appendix C:	12
Danh sách hình	13
List of Tables	14
No table of figures entries found.References	14
 


1.	Giới thiệu (Introduction)
(Introduction to the motivation, Objectives, and main Contents of the project)
Mục tiêu của dự án: Vận dụng các kiến thức, kỹ năng đã được học để thiết kế và thực thi một bộ đếm số bước chân. Hệ thống được thiết kế để có thể thực hiện bằng các mô-đun cảm biến gia tốc và các ngoại vi có sẵn trên bo mạch FRDM-KL46z. Sinh viên cũng có thể sử dụng một bo mạch tương đương để thực hiện dự án.
2.	Yêu cầu đối với thiết kế (Requirements)
2.1.	Yêu cầu đối với thiết kế
Yêu cầu thiết kế: 
-	Chức năng: Đếm số bước chân khi người sử dụng thiết bị di chuyển và hiển thị kết quả trên màn LCD.
-	Các đầu vào: 
o	Hệ thống sử dụng cảm biến gia tốc MMA8451 để đo số bước chân.
o	SW1 để chuyển đổi bộ đếm bước chân hoạt động giữa trạng thái hoạt động và trạng thái dừng. Khi bộ đếm dừng hoạt động, nếu bấm SW1 bộ đếm chuyển sang trạng thái hoạt động, và ngược lại. Khi chuyển từ trạng thái dừng sang trạng thái hoạt động, bộ đếm tiếp tục đếm từ số bước chân đang hiển thị trên LCD.
o	SW2 để xóa (reset) kết quả đếm của bộ đếm về không.
-	Các đầu ra: 
o	Hệ thống có 2 lối ra trạng thái: LED xanh nhấp nháy với tần số 1Hz khi bộ đếm hoạt động; tắt khi hệ thống dừng hoạt động. LED đỏ sáng khi hệ thống dừng hoạt động; tắt khi hệ thống hoạt động.
o	LCD: Hiện thị số bước chân 
-	Bộ đếm sử dụng một timer để xác định khoảng thời gian nhấp nháy LED xanh.
2.2.	Đặc tả kỹ thuật (Specification)
2.2.1.	Mô tả chung:
Mục đích của hệ thống là thiết kế và thực thi một bộ đếm số bước chân, sử dụng các mô-đun cảm biến gia tốc và các ngoại vi có sẵn trên bo mạch FRDM-KL46z hoặc bo mạch tương đương.
Hệ thống sẽ đếm số bước chân khi người sử dụng di chuyển và hiển thị kết quả lên màn hình LCD.
Hệ thống có các đầu vào bao gồm cảm biến gia tốc MMA8451, SW1 để chuyển đổi trạng thái hoạt động và trạng thái dừng, SW2 để reset kết quả đếm của bộ đếm.
Hệ thống có các đầu ra bao gồm LED xanh nhấp nháy khi bộ đếm hoạt động, LED đỏ sáng khi hệ thống dừng hoạt động và màn hình LCD hiển thị số bước chân.
Bộ đếm sử dụng một timer để xác định khoảng thời gian nhấp nháy LED xanh.
2.2.2.	 Các đặc tả chi tiết:
a)	Cảm biến gia tốc MMA8451:
Cảm biến MMA8451 được sử dụng để đo số bước chân.
Cảm biến được kết nối với bo mạch FRDM-KL46z hoặc bo mạch tương đương thông qua các giao diện phù hợp.
Dữ liệu từ cảm biến được sử dụng để đếm số bước chân.
b)	 SW1 (Chuyển đổi bộ đếm):
SW1 được sử dụng để chuyển đổi trạng thái hoạt động và trạng thái dừng của bộ đếm.
Khi bộ đếm đang ở trạng thái dừng, nhấn SW1 để chuyển sang trạng thái hoạt động.
Khi bộ đếm đang ở trạng thái hoạt động, nhấn SW1 để chuyển sang trạng thái dừng.
Khi chuyển từ trạng thái dừng sang trạng thái hoạt động, bộ đếm tiếp tục đếm từ số bước chân đang hiển thị trên LCD.
c)	SW2 (Reset bộ đếm):
SW2 được sử dụng để reset kết quả đếm của bộ đếm về 0.
Khi nhấn SW2, kết quả đếm trên LCD sẽ được đặt về 0.
d)	 LED:
Hệ thống có hai LED: LED xanh và LED đỏ.
LED xanh nhấp nháy với tần số 1Hz khi bộ đếm đang hoạt động.
LED xanh tắt khi hệ thống dừng hoạt động.
LED đỏ sáng khi hệ thống dừng hoạt động.
LED đỏ tắt khi hệ thống hoạt động.
e)	Màn hình LCD:
Màn hình LCD được sử dụng để hiển thị số bước chân.
Số bước chân được cập nhật liên tục trên màn hình LCD.
Khi nhấn SW2 để reset bộ đếm, số bước chân trên màn hình LCD sẽ được đặt về 0.
f)	Timer:
Bộ đếm sử dụng một timer để xác định khoảng thời gian nhấp nháy LED xanh.
Timer được cấu hình để phát tín hiệu tắt/bật LED xanh với tần số 1Hz khi bộ đếm đang hoạt động.
3.	Thực hiện hệ thống (Implementation)
3.1.	Kiến trúc phần cứng (Hardware Architecture)
Miêu tả chức năng của các ngoại vi có sẵn trên bo mạch FRDM-KL46Z được sử dụng để thực hiện hệ thống đếm bước chân (Bảng 1) ;


Bảng 1: Mô tả các ngoại vi được sử dụng.
STT	Tên ngoại vi	Chức năng
1	SW1	Start/Stop bộ đếm

Các mô-đun phần cứng trên bo mạch FRDM-KL46Z được sử dụng để thực hiện bộ điều khiển như sau:

 
Hình 1. Giao diện ghép nối I/O của đơn vị Sorting Unit.

3.1.1.	Khối xử lý trung tâm
 
 
3.1.2.	Cảm biến đầu vào
 
Hình 2: Cấu trúc của cảm biến đầu vào.
 
Bảng 3. Kết nối của cảm biến gia tốc
3.1.3.	Các LED
 
Hình 3: Các LED trên bo mạch FRDM-KL46Z.
Bảng 2. Kết nối các LED trên bo mạch KL46Z
LED	KL46Z Pin
Red	PTE29
Green	PTD5

3.1.4.	LCD
 
 
Bảng 4: Kết nối sLCD
3.2.	Lập trình phần mềm

3.2.1.	Thiết lập Clock cho hệ thống

3.2.2.	Khởi tạo các LED
void InitLEDGreen(void){ 
SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; 
PORTD->PCR[5] = PORT_PCR_MUX(1u); 
PTD->PDDR |= (1u<<5); 
}
void InitLEDdo(){ 
SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; 
PORTE->PCR[29] = PORT_PCR_MUX(1u); 
PTE->PDDR |= (1u<<29); 
}
3.2.3.	Khởi tạo các Switch
a)	Cấp xung clock cho cổng GPIO:
SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; /* Enable clock for port C */
b)	Thiết lập ngắt cho Switches:
PORTC->PCR[3] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | 
	PORT_PCR_PS_MASK | PORT_PCR_IRQC(0xA);
3.2.4.	Khởi tạo Systick Timer
void init_systick(void){
	SysTick->LOAD = (48000000/16/1000);	//Interrupt at every 1ms
	NVIC_SetPriority(SysTick_IRQn, 4);

	SysTick->VAL = 0;			//Force reloading the counter value
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk |	//Enable Systick timer
	SysTick_CTRL_ENABLE_Msk;
	NVIC_EnableIRQ(SysTick_IRQn);	//Enable Systick timer interrupt
}
3.2.5.	Thiết lập mức ưu tiên cho các ngắt
Ngắt reset: mức 0
Ngắt systick timer : mức 4 : 
NVIC_SetPriority(SysTick_IRQn, 4);
3.2.6.	Chương trình điều khiển (Hàm main())
int main() {
	I2C0_init();
	init_systick();
	init_mma();
	
	calibrate(xval,yval,zval,&xavg,&yavg,&zavg);
	delay(1000);
	
	volatile static int i = 0 ;
	while(1) {
		i++;
		if(i < 100) {
		step_count = detect_step(step_count,i);
		slcd_display_decimal(step_count);
		}
		else {
			i = 0;
		}
	}
}
4.	Kiểm chứng (Validation)



5.	Kết luận (Conclusion) 

 
Appendix A: Schematic

 
Appendix B: Code
https://github.com/dh266/btlnhung 
Appendix C: 


Danh sách Bảng (List of Tables)
Bảng 1: Mô tả các ngoại vi được sử dụng.	7
Bảng 2. Kết nối các LED trên bo mạch KL46Z	9
 
References
[1]  	

