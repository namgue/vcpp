#include "yuhanCG.h"


void DrawBonobono(HWND hWnd, HDC hdc, int blink) {

    HBRUSH blueBrush = CreateSolidBrush(RGB(127, 200, 255));
    SelectObject(hdc, blueBrush);
    int centerX = (drawingRect.left + drawingRect.right) / 2;
    int centerY = (drawingRect.top + drawingRect.bottom) / 2;
    int radius = min((drawingRect.right - drawingRect.left) / 2, (drawingRect.bottom - drawingRect.top) / 2);
    Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
    DeleteObject(blueBrush);

    HBRUSH mouseBrush = CreateSolidBrush(RGB(255, 150, 255));
    SelectObject(hdc, mouseBrush);
    Ellipse(hdc, centerX - 25, centerY, centerX + 25, centerY + 80);
    DeleteObject(mouseBrush);

    HBRUSH whitenose1Brush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, whitenose1Brush);
    Ellipse(hdc, centerX - 50, centerY, centerX, centerY + 40);
    DeleteObject(whitenose1Brush);

    HBRUSH whitenose2Brush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, whitenose2Brush);
    Ellipse(hdc, centerX, centerY, centerX + 50, centerY + 40);
    DeleteObject(whitenose2Brush);

    HBRUSH noseBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, noseBrush);
    Ellipse(hdc, centerX - 20, centerY - 20, centerX + 20, centerY + 20);
    DeleteObject(noseBrush);
    if (blink == 0) {
        HBRUSH spaceeyeBrush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, spaceeyeBrush);
        MoveToEx(hdc, centerX - 110, centerY - 20, NULL);
        LineTo(hdc, centerX - 130, centerY - 40);
        MoveToEx(hdc, centerX - 110, centerY - 20, NULL);
        LineTo(hdc, centerX - 130, centerY);
        MoveToEx(hdc, centerX + 110, centerY - 20, NULL);
        LineTo(hdc, centerX + 130, centerY - 40);
        MoveToEx(hdc, centerX + 110, centerY - 20, NULL);
        LineTo(hdc, centerX + 130, centerY);
        DeleteObject(spaceeyeBrush);
    }
    else {
        HBRUSH eye1Brush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, eye1Brush);
        Ellipse(hdc, centerX - 120, centerY - 20, centerX - 110, centerY);
        DeleteObject(eye1Brush);

        HBRUSH eye2Brush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, eye2Brush);
        Ellipse(hdc, centerX + 110, centerY - 20, centerX + 120, centerY);
        DeleteObject(eye2Brush);

        HBRUSH whiteeye1Brush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, whiteeye1Brush);
        Ellipse(hdc, centerX - 117, centerY - 16, centerX - 112, centerY - 8);
        DeleteObject(whiteeye1Brush);

        HBRUSH whiteeye2Brush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, whiteeye2Brush);
        Ellipse(hdc, centerX + 112, centerY - 16, centerX + 117, centerY - 8);
        DeleteObject(whiteeye2Brush);
    }

    HBRUSH mustacheBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, mustacheBrush);
    MoveToEx(hdc, centerX - 30, centerY + 15, NULL);
    LineTo(hdc, centerX - 70, centerY + 5);
    MoveToEx(hdc, centerX - 30, centerY + 25, NULL);
    LineTo(hdc, centerX - 70, centerY + 40);
    MoveToEx(hdc, centerX + 30, centerY + 15, NULL);
    LineTo(hdc, centerX + 70, centerY + 5);
    MoveToEx(hdc, centerX + 30, centerY + 25, NULL);
    LineTo(hdc, centerX + 70, centerY + 40);
    DeleteObject(mustacheBrush);

}

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {

    int centerX = (left + right) / 2;
    int centerY = (top + bottom) / 2;
    int radius = min((right - left) / 2, (bottom - top) / 2);

    HBRUSH hBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hBrush);

    int earRadius = radius / 3;

    int leftearX = centerX - earRadius * 2;
    int leftearY = centerY - earRadius * 2;
    HBRUSH hLeftearBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hLeftearBrush);
    Ellipse(hdc, leftearX - earRadius, leftearY - earRadius, leftearX + earRadius, leftearY + earRadius);
    DeleteObject(hLeftearBrush);


    int rightearX = centerX - earRadius * -2;
    int rightearY = centerY - earRadius * 2;
    HBRUSH hRightearBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hRightearBrush);
    Ellipse(hdc, rightearX - earRadius, rightearY - earRadius, rightearX + earRadius, rightearY + earRadius);
    DeleteObject(hRightearBrush);


    Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);


    int eyeRadius = radius / 14;


    int leftEyeX = centerX - eyeRadius * 9;
    int leftEyeY = centerY - eyeRadius;
    HBRUSH hLeftEyeBrush = CreateSolidBrush(RGB(0, 0, 0)); 
    SelectObject(hdc, hLeftEyeBrush);
    Ellipse(hdc, leftEyeX - eyeRadius, leftEyeY - eyeRadius, leftEyeX + eyeRadius, leftEyeY + eyeRadius);
    DeleteObject(hLeftEyeBrush);


    int rightEyeX = centerX + eyeRadius * 9;
    int rightEyeY = centerY - eyeRadius;
    HBRUSH hRightEyeBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hRightEyeBrush);
    Ellipse(hdc, rightEyeX - eyeRadius, rightEyeY - eyeRadius, rightEyeX + eyeRadius, rightEyeY + eyeRadius);
    DeleteObject(hRightEyeBrush);


    int eyebrowWidth = radius / 12;
    int eyebrowHeight = radius / 12;


    int leftEyebrowStartX = centerX - eyebrowWidth * 8.5;
    int leftEyebrowStartY = centerY - eyebrowHeight * 4;
    int leftEyebrowEndX = leftEyebrowStartX + eyebrowWidth * 3;
    int leftEyebrowEndY = leftEyebrowStartY;
    MoveToEx(hdc, leftEyebrowStartX, leftEyebrowStartY, NULL);
    LineTo(hdc, leftEyebrowEndX, leftEyebrowEndY);

    int eyebrowWidth2 = radius / 12;
    int eyebrowHeight2 = radius / 12;


    int leftEyebrowStartX2 = centerX - eyebrowWidth2 * 8.5;
    int leftEyebrowStartY2 = centerY - eyebrowHeight2 * 4.2;
    int leftEyebrowEndX2 = leftEyebrowStartX2 + eyebrowWidth2 * 3;
    int leftEyebrowEndY2 = leftEyebrowStartY2;

    MoveToEx(hdc, leftEyebrowStartX2, leftEyebrowStartY2, NULL);
    LineTo(hdc, leftEyebrowEndX2, leftEyebrowEndY2);

    int eyebrowWidth3 = radius / 12;
    int eyebrowHeight3 = radius / 12;


    int leftEyebrowStartX3 = centerX - eyebrowWidth3 * 8.5;
    int leftEyebrowStartY3 = centerY - eyebrowHeight3 * 4.4;
    int leftEyebrowEndX3 = leftEyebrowStartX3 + eyebrowWidth3 * 3;
    int leftEyebrowEndY3 = leftEyebrowStartY3;

    MoveToEx(hdc, leftEyebrowStartX3, leftEyebrowStartY3, NULL);
    LineTo(hdc, leftEyebrowEndX3, leftEyebrowEndY3);



    int rightEyebrowStartX = centerX + eyebrowWidth * 6;
    int rightEyebrowStartY = centerY - eyebrowHeight * 4;
    int rightEyebrowEndX = rightEyebrowStartX + eyebrowWidth * 3;
    int rightEyebrowEndY = rightEyebrowStartY;

    MoveToEx(hdc, rightEyebrowStartX, rightEyebrowStartY, NULL);
    LineTo(hdc, rightEyebrowEndX, rightEyebrowEndY);

    int rightEyebrowStartX2 = centerX + eyebrowWidth2 * 6;
    int rightEyebrowStartY2 = centerY - eyebrowHeight2 * 4.2;
    int rightEyebrowEndX2 = rightEyebrowStartX2 + eyebrowWidth2 * 3;
    int rightEyebrowEndY2 = rightEyebrowStartY2;

    MoveToEx(hdc, rightEyebrowStartX2, rightEyebrowStartY2, NULL);
    LineTo(hdc, rightEyebrowEndX2, rightEyebrowEndY2);


    int rightEyebrowStartX3 = centerX + eyebrowWidth3 * 6;
    int rightEyebrowStartY3 = centerY - eyebrowHeight3 * 4.4;
    int rightEyebrowEndX3 = rightEyebrowStartX3 + eyebrowWidth3 * 3;
    int rightEyebrowEndY3 = rightEyebrowStartY3;

    MoveToEx(hdc, rightEyebrowStartX3, rightEyebrowStartY3, NULL);
    LineTo(hdc, rightEyebrowEndX3, rightEyebrowEndY3);

    int RadiusNose = radius / 6;

    int leftNoseX = centerX - RadiusNose;
    int leftNoseY = centerY - RadiusNose * (-1);
    HBRUSH hLeftNoseBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hLeftNoseBrush);
    Ellipse(hdc, leftNoseX - RadiusNose, leftNoseY - RadiusNose, leftNoseX + RadiusNose, leftNoseY + RadiusNose);
    DeleteObject(hLeftNoseBrush);

    int rightNoseX = centerX - RadiusNose * -1;
    int rightNoseY = centerY - RadiusNose * -1;
    HBRUSH hRightNoseBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hRightNoseBrush);
    Ellipse(hdc, rightNoseX - RadiusNose, rightNoseY - RadiusNose, rightNoseX + RadiusNose, rightNoseY + RadiusNose);
    DeleteObject(hRightNoseBrush);
}

void DrawBox(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {

    HBRUSH hBrush = CreateSolidBrush(RGB(150, 150, 150));
    SelectObject(hdc, hBrush);
    Rectangle(hdc, left, top, right, bottom);
}

void DrawCircle(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {


    HBRUSH hBrush = CreateSolidBrush(RGB(200, 200, 100));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, left, top, right, bottom);

}
void DrawCube(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    SelectObject(hdc, hPen);

    int frontLeftTopX = left;
    int frontLeftTopY = top;
    int frontRightTopX = right;
    int frontRightTopY = top;
    int frontLeftBottomX = left;
    int frontLeftBottomY = bottom;
    int frontRightBottomX = right;
    int frontRightBottomY = bottom;

    int backLeftTopX = left - 70;  
    int backLeftTopY = top - 70;   
    int backRightTopX = right - 70;
    int backRightTopY = top - 70;   
    int backLeftBottomX = left - 70; 
    int backLeftBottomY = bottom - 70; 
    int backRightBottomX = right - 70; 
    int backRightBottomY = bottom - 70; 

   
    MoveToEx(hdc, frontLeftTopX, frontLeftTopY, NULL);
    LineTo(hdc, frontRightTopX, frontRightTopY);
    LineTo(hdc, frontRightBottomX, frontRightBottomY);
    LineTo(hdc, frontLeftBottomX, frontLeftBottomY);
    LineTo(hdc, frontLeftTopX, frontLeftTopY);

    MoveToEx(hdc, frontLeftTopX, frontLeftTopY, NULL);
    LineTo(hdc, backLeftTopX, backLeftTopY);

    MoveToEx(hdc, frontRightTopX, frontRightTopY, NULL);
    LineTo(hdc, backRightTopX, backRightTopY);

    MoveToEx(hdc, frontRightBottomX, frontRightBottomY, NULL);
    LineTo(hdc, backRightBottomX, backRightBottomY);

    MoveToEx(hdc, frontLeftBottomX, frontLeftBottomY, NULL);
    LineTo(hdc, backLeftBottomX, backLeftBottomY);

    MoveToEx(hdc, backLeftTopX, backLeftTopY, NULL);
    LineTo(hdc, backRightTopX, backRightTopY);
    LineTo(hdc, backRightBottomX, backRightBottomY);
    LineTo(hdc, backLeftBottomX, backLeftBottomY);
    LineTo(hdc, backLeftTopX, backLeftTopY);

    DeleteObject(hPen);
}