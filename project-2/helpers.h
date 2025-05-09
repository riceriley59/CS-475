#pragma once

void write_csv(const std::string&, const std::vector<std::string>&);

void InitBarrier(int);
void WaitBarrier();

float Ranf( float, float );
int	Ranf( int, int );
float SQR(float);

float InchesToCM(float);
float FarenheitToCelcius(float);
