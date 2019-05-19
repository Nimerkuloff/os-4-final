// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "decoration.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
Decoration dec1;
Decoration dec2;
int mode;
DynamicArray<TShape*>shapes1;
DynamicArray<TShape*>shapes2;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	shapes1.Length = 10;
	for (int i = 0; i < shapes1.Length; i++) {
		shapes1[i] = new TShape(this);
		shapes1[i]->Parent = this;
		shapes1[i]->Shape = stCircle;
		shapes1[i]->Brush->Color = clWhite;

		shapes1[i]->Height = 8;
		shapes1[i]->Width = 8;
		shapes1[i]->Top = 110 + i * 1;
		shapes1[i]->Left = 140 + i * 10;
		shapes1[i]->Visible = true;

	}
	dec1.getShapes(shapes1);

	shapes2.Length = 10;
	for (int i = 0; i < shapes2.Length; i++) {
		shapes2[i] = new TShape(this);
		shapes2[i]->Parent = this;
		shapes2[i]->Shape = stCircle;
		shapes2[i]->Brush->Color = clWhite;

		shapes2[i]->Height = 15;
		shapes2[i]->Width = 15;
		shapes2[i]->Top = 200 + i * 1;
		shapes2[i]->Left = 100 + i * 18;
		shapes2[i]->Visible = true;

	}
	dec2.getShapes(shapes2);

}

// ---------------------------------------------------------------------------

void __fastcall TForm1::ToggleSwitch1Click(TObject *Sender) {

	if (ToggleSwitch1->IsOn()) {
		dec1.start();
	}
	else {
		dec1.stop();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton1Click(TObject *Sender) {
	mode = 1;
	dec1.setMode(mode);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender) {
	mode = 2;
	dec1.setMode(mode);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton3Click(TObject *Sender) {
	mode = 3;
	dec1.setMode(mode);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton4Click(TObject *Sender) {
	mode = 1;
	dec2.setMode(mode);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton5Click(TObject *Sender) {
	mode = 2;
	dec2.setMode(mode);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton6Click(TObject *Sender) {
	mode = 3;
	dec2.setMode(mode);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::ToggleSwitch2Click(TObject *Sender) {
	if (ToggleSwitch2->IsOn()) {
		dec2.start();
	}
	else {
		dec2.stop();
	}
}
// ---------------------------------------------------------------------------
