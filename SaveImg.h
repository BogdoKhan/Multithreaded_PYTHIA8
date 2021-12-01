#pragma once
#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TPad.h"
#include "TPaveText.h"

#include <sys/stat.h>
#include <iostream>

using namespace std;

void SavePNGandEPS(TCanvas* mycanv, bool isEPS);
void MakeDir(const string& dirpath, const string& dirname);

void SavePNGandEPS(TCanvas* mycanv, bool isEPS){
	MakeDir("../", "Images");
	cout<< "Saving image..." << endl;
	//save image
	gROOT->ProcessLine("TImage *img = TImage::Create();");
	TString nameBase =mycanv->GetTitle();
	//if flag isEPS is set, save as EPS and leave function
	if (isEPS) {
		TString nameEPS = nameBase + ".eps";
		cout << mycanv->GetName() << "->SaveAs(\"" << nameEPS.Data() << "\");" << endl;
		return ;
	}//else proceed with PNG
	TString namePNG = nameBase + ".png";
	TString OutImg = "img->FromPad(" + (TString) (mycanv->GetName()) + "); img->WriteImage(\"../Images/" + namePNG.Data() + "\");";
	gROOT->ProcessLine(OutImg);
}


void MakeDir(const string& dirpath, const string& dirname){
	string path = dirpath + dirname;
	const char* folder = path.c_str();
	//folder = "./Results";
	struct stat sb;

	if (stat(folder, &sb) != 0 && !S_ISDIR(sb.st_mode)) {
		mkdir(folder, 0755);
	} 
}

