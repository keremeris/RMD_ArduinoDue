/*
 Copyright (c) 2012 Arduino LLC.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <MouseController.h>

extern "C" {
void __mouseControllerEmptyCallback() { }
}

void mouseClicked()  __attribute__ ((weak, alias("__mouseControllerEmptyCallback")));
void mouseDragged()  __attribute__ ((weak, alias("__mouseControllerEmptyCallback")));
void mouseMoved()    __attribute__ ((weak, alias("__mouseControllerEmptyCallback")));
void mousePressed()  __attribute__ ((weak, alias("__mouseControllerEmptyCallback")));
void mouseReleased() __attribute__ ((weak, alias("__mouseControllerEmptyCallback")));
void tested() __attribute__ ((weak, alias("__mouseControllerEmptyCallback")));
int MouseController::getXChange() {
	int r = dx;
	dx = 0;
	return r;
}
void MouseController::getTest(uint8_t *buf) {
	for(uint8_t i=0;i<20;i++)
		buf[i] = tinfo[i];
}

int MouseController::getYChange() {
	int r = dy;
	dy = 0;
	return r;
}

void MouseController::OnMouseMove(MOUSEINFO *mi) {
	dx += mi->dX;
	dy += mi->dY;
	if (buttons != 0)
		mouseDragged();
	else
		mouseMoved();
}

void MouseController::OnLeftButtonUp(MOUSEINFO *mi) {
	buttons &= ~LEFT_BUTTON;
	mouseReleased();
	mouseClicked();
}

void MouseController::OnLeftButtonDown(MOUSEINFO *mi) {
	buttons |= LEFT_BUTTON;
	mousePressed();
}

void MouseController::OnMiddleButtonUp(MOUSEINFO *mi) {
	buttons &= ~MIDDLE_BUTTON;
	mouseReleased();
	mouseClicked();
}

void MouseController::OnMiddleButtonDown(MOUSEINFO *mi) {
	buttons |= MIDDLE_BUTTON;
	mousePressed();
}

void MouseController::OnRightButtonUp(MOUSEINFO *mi) {
	buttons &= ~RIGHT_BUTTON;
	mouseReleased();
	mouseClicked();
}

void MouseController::OnRightButtonDown(MOUSEINFO *mi) {
	buttons |= RIGHT_BUTTON;
	mousePressed();
}

void MouseController::TestFunction(TESTINFO *ti) {
	for (uint8_t i=0;i<20;i++)
		tinfo[i] = ti->hidInfo[i];
	tested();
}


