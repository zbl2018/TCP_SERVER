#include "include/control_car.h"
#include <iostream>

//普通模式：向前移动的速度和角度
void car::Move(short int speed,int angle)
{
	int cnt=0, sum=0;
	data_send[cnt++]=0xFA;
	data_send[cnt++]=0xAA;
	data_send[cnt++]=0x00;
	data_send[cnt++]=0x03;
	data_send[cnt++]=angle;
	data_send[cnt++]=speed >> 8;
	data_send[cnt++]=(unsigned char)speed;
	
	for(int i=0;i<cnt;i++)
		sum +=data_send[i];
	data_send[cnt++]=sum;
}
//原地模式：绕原地来运动
void car::Circle(short int speed)
{
	int cnt=0,sum=0;
	data_send[cnt++]=0xFA;
	data_send[cnt++]=0xAA;	
	data_send[cnt++]=0x01;
	data_send[cnt++]=0x02;
	data_send[cnt++]=speed >> 8;
	data_send[cnt++]=(unsigned char)speed;
	
	for(int i=0;i<cnt;i++)
		sum +=data_send[i];
	data_send[cnt++]=sum;
}
//停车模式
void car::Stop()
{
	int cnt=0,sum=0;
	data_send[cnt++]=0xFA;
	data_send[cnt++]=0xAA;	
	data_send[cnt++]=0x02;
	data_send[cnt++]=0x01;
	data_send[cnt++]=0x00;

	for(int i=0;i<cnt;i++)
		sum +=data_send[i];
	data_send[cnt++]=sum;
}
//给小车的指令
void car::run(int mode, int angle, float velosity)
{
	switch(mode)
	{
	case 0:
		Move((short int)(velosity * 60 * 100 / perimeter), angle);
		break;
	case 1:
		Circle((short int)(velosity * 60 * 100 / perimeter));
		break;
	case 2:
		Stop();
		break;
	default:
		break;	
	}
}

void car::DataReceive(unsigned char* data_receive, int n)
{
	short len;
	short func_word;
	for (int i = 0; i < n - 4; i++)
	{
		short sum = 0;
		if ((short)data_receive[i] == 0xAA && (short)data_receive[i + 1] == 0xAA && (short)data_receive[i + 3] < 50)
		{
			len = (short)data_receive[i + 3];
			if ((len + 1) <= (n - i - 4))//长度足够的话
			{
				for (int j = i; j <= i + len + 3; j++)
				{
					sum += data_receive[j];
				}
				if ((sum & 0x00FF) == (short)data_receive[i + len + 4])//校验通过
				{
					func_word = (short)data_receive[i + 2];
					if (func_word == 0x00)
					{
						mode_data = (short)data_receive[i + 4];
						angle_data = (short)(data_receive[i + 5]);
						speed_data = (short)((data_receive[i + 6] << 8) | data_receive[i + 7]);
					}
					if (func_word == 0x01)
					{
						sv1_ac_data = (short)((data_receive[i + 4] << 8) | data_receive[i + 5]);
						sv1_ang_data = (float)(sv1_ac_data / 100.0f);

						sv2_ac_data = (short)((data_receive[i + 6] << 8) | data_receive[i + 7]);
						sv2_ang_data = (float)(sv2_ac_data / 100.0f);

						sv3_ac_data = (short)((data_receive[i + 8] << 8) | data_receive[i + 9]);
						sv3_ang_data = (float)(sv3_ac_data / 100.0f);

						sv4_ac_data = (short)((data_receive[i + 10] << 8) | data_receive[i + 11]);
						sv4_ang_data = (float)(sv4_ac_data / 100.0f);
					}
					else if (func_word == 0x02)
					{
						cur1_data = (short)((data_receive[i + 4] << 8) | data_receive[i + 5]) * 0.01f;
						cur2_data = (short)((data_receive[i + 6] << 8) | data_receive[i + 7]) * 0.01f;
						cur3_data = (short)((data_receive[i + 8] << 8) | data_receive[i + 9]) * 0.01f;
						cur4_data = (short)((data_receive[i + 10] << 8) | data_receive[i + 11]) * 0.01f;

						m1_data = (short)((data_receive[i + 12] << 8) | data_receive[i + 13]);
						m2_data = (short)((data_receive[i + 14] << 8) | data_receive[i + 15]);
						m3_data = (short)((data_receive[i + 16] << 8) | data_receive[i + 17]);
						m4_data = (short)((data_receive[i + 18] << 8) | data_receive[i + 19]);
					}
					else if (func_word == 0x03)
					{
						pul1_data = (int)((data_receive[i + 4] << 24) | (data_receive[i + 5] << 16) | (data_receive[i + 6] << 8) | data_receive[i + 7]);
                        pul2_data = (int)((data_receive[i + 8] << 24) | (data_receive[i + 9] << 16) | (data_receive[i + 10] << 8) | data_receive[i + 11]);
                        pul3_data = (int)((data_receive[i + 12] << 24) | (data_receive[i + 13] << 16) | (data_receive[i + 14] << 8) | data_receive[i + 15]);
                        pul4_data = (int)((data_receive[i + 16] << 24) | (data_receive[i + 17] << 16) | (data_receive[i + 18] << 8) | data_receive[i + 19]);

						dis1_data = (int)(pul1_data / 90.0 * perimeter);
						dis2_data = (int)(pul2_data / 90.0 * perimeter);
						dis3_data = (int)(pul3_data / 90.0 * perimeter);
						dis4_data = (int)(pul4_data / 90.0 * perimeter);
					}
					else if (func_word == 0x04)
					{
						us1_data = (short)(data_receive[i + 4]);
						us2_data = (short)(data_receive[i + 5]);
						us3_data = (short)(data_receive[i + 6]);
						us4_data = (short)(data_receive[i + 7]);
						us5_data = (short)(data_receive[i + 8]);
						us6_data = (short)(data_receive[i + 9]);
						us7_data = (short)(data_receive[i + 10]);
						us8_data = (short)(data_receive[i + 11]);
						obstacle_data = (short)(data_receive[i + 12]);
						dis_keep_data = (short)(data_receive[i + 13]);
					}
					else if (func_word == 0x05)
					{
						cell1_data = (short)((data_receive[i + 4] << 8) | data_receive[i + 5]) * 0.001f;
						cell2_data = (short)((data_receive[i + 6] << 8) | data_receive[i + 7]) * 0.001f;
						cell3_data = (short)((data_receive[i + 8] << 8) | data_receive[i + 9]) * 0.001f;
						cell4_data = (short)((data_receive[i + 10] << 8) | data_receive[i + 11]) * 0.001f;
						cell5_data = (short)((data_receive[i + 12] << 8) | data_receive[i + 13]) * 0.001f;
						cell6_data = (short)((data_receive[i + 14] << 8) | data_receive[i + 15]) * 0.001f;
						cell7_data = (short)((data_receive[i + 16] << 8) | data_receive[i + 17]) * 0.001f;
						cell8_data = (short)((data_receive[i + 18] << 8) | data_receive[i + 19]) * 0.001f;
						cell9_data = (short)((data_receive[i + 20] << 8) | data_receive[i + 21]) * 0.001f;
						cell10_data = (short)((data_receive[i + 22] << 8) | data_receive[i + 23]) * 0.001f;
						cell11_data = (short)((data_receive[i + 24] << 8) | data_receive[i + 25]) * 0.001f;
						cell12_data = (short)((data_receive[i + 26] << 8) | data_receive[i + 27]) * 0.001f;
					}
					else if (func_word == 0x06)
					{
						max_voltage_data = ((data_receive[i + 4] << 8) | data_receive[i + 5]) * 0.001f;
                        min_voltage_data = ((data_receive[i + 6] << 8) | data_receive[i + 7]) * 0.001f;
                        max_voltage_pos_data = ((data_receive[i + 8] << 8) | data_receive[i + 9]);
                        min_voltage_pos_data = ((data_receive[i + 10] << 8) | data_receive[i + 11]);
                        voltage_diff_data = ((data_receive[i + 12] << 8) | data_receive[i + 13]) * 0.001f;
                        avg_voltage_data = ((data_receive[i + 14] << 8) | data_receive[i + 15]) * 0.001f;
                        total_voltage_data = ((data_receive[i + 16] << 8) | data_receive[i + 17]) * 0.1f;

                        charge_cur_data = ((data_receive[i + 18] << 8) | data_receive[i + 19]) * 0.1f;
                        discharge_cur_data = ((data_receive[i + 20] << 8) | data_receive[i + 21]) * 0.1f;

                        soc_data = ((data_receive[i + 22] << 8) | data_receive[i + 23]) * 0.01f;
						std::cout << "gjygjy" << std::endl;
					}
					else if (func_word == 0x07)
					{
						temperature1_data = (short)((data_receive[i + 4] << 8) | data_receive[i + 5]) * 0.1f;
						temperature2_data = (short)((data_receive[i + 6] << 8) | data_receive[i + 7]) * 0.1f;
						temperature3_data = (short)((data_receive[i + 8] << 8) | data_receive[i + 9]) * 0.1f;
						temperature4_data = (short)((data_receive[i + 10] << 8) | data_receive[i + 11]) * 0.1f;
						temperature5_data = (short)((data_receive[i + 12] << 8) | data_receive[i + 13]) * 0.1f;
						temperature6_data = (short)((data_receive[i + 14] << 8) | data_receive[i + 15]) * 0.1f;

						max_temp_data = (short)((data_receive[i + 16] << 8) | data_receive[i + 17]) * 0.1f;
						min_temp_data = (short)((data_receive[i + 18] << 8) | data_receive[i + 19]) * 0.1f;
						avg_temp_data = (short)((data_receive[i + 20] << 8) | data_receive[i + 21]) * 0.1f;
						envirmnt_temp_data = (short)((data_receive[i + 22] << 8) | data_receive[i + 23]) * 0.1f;
					}
					else if (func_word == 0x08)
					{
						Rc_data = (int)((data_receive[i + 4] << 8) | data_receive[i + 5]);
						Wr_data = (float)((int)((data_receive[i + 6] << 24) | (data_receive[i + 7] << 16) | (data_receive[i + 8] << 8) | data_receive[i + 9]) * 0.00001f);
					}
				}
			}
		}
	}
}
