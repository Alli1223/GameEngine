#pragma once
//https://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB
class HSL
{
public:
	double Hue;
	double Saturation;
	double Luminance;

	HSL();
	HSL(int H, int S, int L);
	vec3 TurnToRGB();

	HSL TurnToHSL(const vec3& C);
	const double D_EPSILON = 0.00000000000001;
private:
	
	double HueToRGB(double arg1, double arg2, double H);
};
