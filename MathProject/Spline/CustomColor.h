#pragma once
class CustomColor
{
public:
    float RedValue;
    float GreenValue;
    float BlueValue;
    CustomColor::CustomColor();
    CustomColor(float redValue, float greenValue, float blueValue) : RedValue(redValue), GreenValue(greenValue), BlueValue(blueValue) {}
    ~CustomColor();
};

