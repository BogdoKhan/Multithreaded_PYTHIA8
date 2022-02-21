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

//THREAD-SAFE RANDOM NUMBER GENERATOR FOR PYTHIA SEED

#if defined (_MSC_VER)  // Visual studio
    #define thread_local __declspec( thread )
#elif defined (__GCC__) // GCC
    #define thread_local __thread
#endif

#include <random>
#include <time.h>
#include <thread>

#include <sys/stat.h>
#include <iostream>

using namespace std;

void SavePNGandEPS(TCanvas* mycanv, bool isEPS);
void MakeDir(const string& dirpath, const string& dirname);
int intRand(const int & min, const int & max, vector<mt19937*>& gens);

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

int intRand(const int & min, const int & max, vector<mt19937*>& gens) {
	mutex addGen_excl;
    static thread_local mt19937* generator = nullptr;
    if (!generator) generator = new mt19937(clock() + std::hash<std::thread::id>()(std::this_thread::get_id()));
    uniform_int_distribution<int> distribution(min, max);
	lock_guard<mutex> lock_Gen(addGen_excl);
	gens.push_back(generator);
    return distribution(*generator);
}
