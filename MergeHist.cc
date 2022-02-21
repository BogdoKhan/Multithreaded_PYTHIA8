#include "TH1.h"
#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "THnSparse.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TProfile.h"
#include "TROOT.h"
#include "TRandom3.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLine.h"

#include <sstream>
#include <string>
#include "ProcFunctions.h"

#include <vector>
#include <map>
#include <iostream>

using namespace std;

int GetSummarySpectrum(const Int_t& seed, const Int_t& TTLow);
void Scaling(Int_t trigRangeLow, Double_t luminosity_OO);
void DoPoisSmearing(Int_t trigRangeLow);
//void MakeDeltaRecoilSp(const Int_t& trigRangeLow_1, const Int_t& trigRangeLow_2);
//void SavePNGandEPS(TCanvas* mycanv, bool isEPS);
//int intRand(const int & min, const int & max, vector<mt19937*>& gens);

//int GetSummarySpectrum(const Int_t& seed, const Int_t& TTLow)
//void Scaling(Int_t trigRangeLow)
//void DoPoisSmearing(Int_t trigRangeLow)
//void MakeDeltaRecoilSp(const Int_t& trigRangeLow_1, const Int_t& trigRangeLow_2)

TString name = "";

enum {kMB, kFIT, kTRIG};  //kMB = pythia min bias,   kFIT =  event triggered with FIT coincidence
TString trg[]={"MB","FIT"};
enum {kOO, kpp, ktr};
TString RType[] = {"OO", "pp"};

TH1D* fhTTHPartLevel[kTRIG];
TH1D* fhRecoilJetPtTTH_PartLevel[kTRIG];
TH2D* fhRecoilJetPhiTTH_PartLevel[kTRIG];

void Sum(TFile *f1, const Int_t& seed, const Int_t& TTLow, const Int_t& ptval){
	Int_t cislo = seed;
	Int_t ttl = TTLow;
	Int_t pthmin = ptval;

	for(Int_t ig = kMB; ig< kTRIG; ig++){
		name = Form("hTT_%s_PartLevel_seed%d_tt_%d_pt%d", trg[ig].Data(), cislo, ttl, pthmin);
		TH1D* htt = (TH1D*) f1->Get(name);
		if(!htt){
			cout << "Wrong pT for this file!" << endl;
			return ;
				 }

		name = Form("fhRecoilJetPt_%s_PartLevel_seed%d_tt_%d_pt%d", trg[ig].Data(), cislo, ttl, pthmin);
		TH1D* hpt = (TH1D*) f1->Get(name);
		if(!hpt){
			cout << "Wrong pT for this file!" << endl;
			return ;
				 }

		name = Form("fhRecoilJetPhi_%s_PartLevel_seed%d_tt_%d_pt%d", trg[ig].Data(),cislo, ttl, pthmin);
		TH2D* hphi = (TH2D*) f1->Get(name);
		if(!hphi){
			cout << "Wrong pT for this file!" << endl;
			return ;
				 }

		name = Form("fHistXsections_%s_%d_tt_%d_pt%d", trg[ig].Data(), cislo, ttl, pthmin);
		TProfile* hxs = (TProfile*) f1->Get(name);
		if(!hxs){
			cout << "Wrong pT for this file!" << endl;
			return ;
				 }

		name = Form("fHistTrials_%s_%d_tt_%d_pt%d", trg[ig].Data(), cislo, ttl, pthmin);
		TH1F* hntr = (TH1F*) f1->Get(name);
		if(!hntr){
			cout << "Wrong pT for this file!" << endl;
			return ;
				 }

		Double_t xsection = hxs->GetMean(2);
		Double_t ntrials =  hntr->Integral();
		Double_t weight = 1;
		if (ntrials != 0) weight = xsection/ntrials;

		fhTTHPartLevel[ig]->Add(htt, weight);
		fhRecoilJetPtTTH_PartLevel[ig]->Add(hpt, weight);
		fhRecoilJetPhiTTH_PartLevel[ig]->Add(hphi, weight);
		delete htt;
		delete hpt;
		delete hphi;
		delete hxs;
		delete hntr;
	}
	cout << "File was added" << endl;
}

int GetSummarySpectrum(const Int_t& seed, const Int_t& TTLow){

	vector<Int_t> pthmin = {4, 11, 21, 36, 56, 84, 117, 156, 200, 249};  //hard bin

	Double_t pTbins3[]   = {-20,-15,-10,-5,-4,-3,-2,-1,0,1,2,3,4,5,10,15,20,25,30,35,40,45,50,60,70,80,100,120,140,160,180,200};
	const Int_t npTbins3 = sizeof(pTbins3)/sizeof(Double_t)-1;

	const Int_t narrPhi=128;
	Double_t arrPhi[narrPhi+1];
	Double_t p = TMath::TwoPi()/narrPhi;

	for(Int_t i=0; i<=narrPhi; i++){
		arrPhi[i] = i*p;
	}

	Int_t cislo = seed;
	Int_t trigRangeLow = TTLow;

	//cout << "Enter seed, TTLow: " << endl;
	//cin >> cislo >> trigRangeLow;

	for(Int_t ig = kMB; ig<kTRIG; ig++){
		name = Form("hTT_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		fhTTHPartLevel[ig] = new TH1D(name.Data(),name.Data(), 100, 0, 100);

		name = Form("fhRecoilJetPt_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		fhRecoilJetPtTTH_PartLevel[ig] = new TH1D(name.Data(), name.Data(), 200, -20, 180);

		name = Form("fhRecoilJetPhi_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		fhRecoilJetPhiTTH_PartLevel[ig] = new TH2D(name.Data(), name.Data(), npTbins3, pTbins3, narrPhi, arrPhi);
	}


	TString filename = "";
	while (filename != "stop") {
		cout << "Enter filename: " << endl;
		cin >> filename;
		if (filename == "stop") {
			break;
		}

		std::string fname = static_cast<std::string>(filename);
		Int_t pos = fname.find("HB") + 2;
		Int_t endpos = fname.find("_", pos);
		std::string pt = fname.substr(pos, endpos - pos);
		Int_t ptval = std::stoi(pt);

		TFile *file = TFile::Open(filename,"READ");
	   	if(!file){
			cout << "Not a file!" << endl;
			break;
		}
		Sum (file, cislo, trigRangeLow, ptval);
	}

	name = Form("Res_tt_%d.root", trigRangeLow);
	TFile *outFile = new TFile(name, "RECREATE");
	outFile->cd();

	for(Int_t ig = kMB; ig<kTRIG; ig++){
		name = Form("%s trigger tracks histogram (Xsection) at %d GeV/c; p_{T}, GeV/c; #sigma, mb", trg[ig].Data(), trigRangeLow);
		fhTTHPartLevel[ig]->SetTitle(name);
		name = Form("%s recoil jets histogram (Xsection) at %d GeV/c; p_{T}, GeV/c; #sigma, mb", trg[ig].Data(), trigRangeLow);
		fhRecoilJetPtTTH_PartLevel[ig]->SetTitle(name);
		name = Form("%s RJ #phi histogram at %d GeV/c", trg[ig].Data(), trigRangeLow);
		fhRecoilJetPhiTTH_PartLevel[ig]->SetTitle(name);

		fhTTHPartLevel[ig]->Write();
		fhRecoilJetPtTTH_PartLevel[ig]->Write();
		fhRecoilJetPhiTTH_PartLevel[ig]->Write();
	}
	outFile->Close();

	for(Int_t igm = kMB; igm<kTRIG; igm++){
		delete fhTTHPartLevel[igm];
		delete fhRecoilJetPtTTH_PartLevel[igm];
		delete fhRecoilJetPhiTTH_PartLevel[igm];
	}
	delete outFile;
	return 0;
}

template<typename T>
T Scaler(T histo, TString& name, const Double_t& factor){
	histo->SetName(name);
	histo->Scale(factor);
	return histo;
}

void Scaling(Int_t trigRangeLow, Double_t luminosity_OO){
	name = Form("Res_tt_%d.root", trigRangeLow);
	TFile* f1 = TFile::Open(name, "UPDATE");
	name = Form("Res_scaled_tt_%d.root", trigRangeLow);
	TFile *outFile = new TFile(name, "RECREATE");
	outFile->cd();
	//Make counts for known luminosities: let us have 4 nb^-1 -> 4 nb^-1 = 4e6 mb^-1;
	//pp-luminosities: 3 pb^-1 = 3e9 mb^-1
	//OO-luminosities: 0.5 nb^-1; 1 nb^-1; 2nb^-1; 4nb^-1;
	//Xsection for OO-collisions: A(O) = 16; Xs(OO) = Xs(pp)*A^2;
	//Double_t luminosity = 4e6; //4 nb^-1 -> 4e6 mb^-1;
	Double_t luminosity = luminosity_OO;
	Double_t luminosity_pp = 3e9;
	Int_t A = 16; //oxygen mass in amu
	Double_t factorOO = A * A * luminosity;

	Double_t integral = 0;

	for(Int_t ig = kMB; ig< kTRIG; ig++){
		name = Form("hTT_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		TH1D* htt = (TH1D*) f1->Get(name);
		TH1D* htt_pp = (TH1D*) htt->Clone();

		name = Form("hTT_OO_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		htt = Scaler(htt, name, factorOO);
		name = Form("%s trigger tracks histogram for OO at %d GeV/c; p_{T}, GeV/c; Counts", trg[ig].Data(), trigRangeLow);
		htt->SetTitle(name);

		htt->Write();
		integral = htt->Integral()/factorOO;
		cout << "OO " << integral << endl;


		name = Form("hTT_pp_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		htt_pp = Scaler(htt_pp, name, luminosity_pp);
		name = Form("%s trigger tracks histogram for pp at %d GeV/c; p_{T}, GeV/c; Counts", trg[ig].Data(), trigRangeLow);
		htt_pp->SetTitle(name);
		htt_pp->Write();
		integral = htt_pp->Integral()/luminosity_pp;
		cout << "pp " << integral << endl;


		name = Form("fhRecoilJetPt_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		TH1D* hpt = (TH1D*) f1->Get(name);
		TH1D* hpt_pp = (TH1D*) hpt->Clone();

		name = Form("fhRecoilJetPt_OO_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		hpt = Scaler(hpt, name, factorOO);
		name = Form("Unsmeared %s recoil jets histogram for OO at %d GeV/c; p_{T}, GeV/c; Counts", trg[ig].Data(), trigRangeLow);
		hpt->SetTitle(name);
		hpt->Write();


		name = Form("fhRecoilJetPt_pp_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		hpt_pp = Scaler(hpt_pp, name, luminosity_pp);
		name = Form("Unsmeared %s recoil jets histogram for pp at %d GeV/c; p_{T}, GeV/c; Counts", trg[ig].Data(), trigRangeLow);
		hpt_pp->SetTitle(name);
		hpt_pp->Write();


		name = Form("fhRecoilJetPhi_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		TH2D* hphi = (TH2D*) f1->Get(name);
		TH2D* hphi_pp = (TH2D*) hphi->Clone();
		name = Form("fhRecoilJetPhi_OO_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		hphi = Scaler(hphi, name, factorOO);
		hphi->Write();

		name = Form("fhRecoilJetPhi_pp_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		hphi_pp = Scaler(hphi_pp, name, luminosity_pp);
		hphi_pp->Write();

	}
	outFile->Close();
}

TH1D* MakePois(TFile* f1, const TString& name) {
	vector<mt19937*> gens;
	TRandom3 gener(intRand(0, 999999, gens));
	TH1D* histo = (TH1D*) f1->Get(name);
	TH1D* Pois_hist = (TH1D*) histo->Clone();
	Int_t nbins = Pois_hist->GetNbinsX();
	for (Int_t in = 1; in <= nbins; in++){
		Int_t binc = Pois_hist->GetBinContent(in);
		binc = gener.TRandom::Poisson(binc);
		Pois_hist->SetBinContent(in, binc);
		Pois_hist->SetBinError(in, TMath::Sqrt(binc));
	}
	cout << "Poisson smearing for " << name << " is done!\n";
	return Pois_hist;
}

void DoPoisSmearing(Int_t trigRangeLow){
	name = Form("Res_scaled_tt_%d.root", trigRangeLow);
	TFile* f1 = TFile::Open(name, "READ");
	name = Form("Res_pois_tt_%d.root", trigRangeLow);
	TFile *outFile = new TFile(name, "RECREATE");
	outFile->cd();

	TH1D* Pois_hist_TT[kTRIG];
	TH1D* Pois_hist_RJ[kTRIG];

	Int_t nbins = 0;
	TRandom3 gener;

	Double_t luminosity = 4e6; //4 nb^-1 -> 4e6 mb^-1;
	Double_t luminosity_pp = 3e9;
	Int_t A = 16; //oxygen mass in amu
	Double_t factorOO = A * A * luminosity;
	Double_t integral = 0;

	for(Int_t ig = kMB; ig< kTRIG; ig++){
		for(Int_t ij = kOO; ij< ktr; ij++){
			name = Form("hTT_%s_%s_PartLevel_tt_%d", RType[ij].Data(), trg[ig].Data(), trigRangeLow);
			//Pois_hist_TT[ig] = MakePois(f1, name);
			TH1D* histo = (TH1D*) f1->Get(name);
			Pois_hist_TT[ig] = (TH1D*) histo->Clone();
			name = Form("%s trigger tracks histogram for %s at %d GeV/c; p_{T}, GeV/c; Counts", trg[ig].Data(), RType[ij].Data(), trigRangeLow);
			Pois_hist_TT[ig]->SetTitle(name);
			Pois_hist_TT[ig]->Write();
			integral = Pois_hist_TT[ig]->Integral();

			name = Form("fhRecoilJetPt_%s_%s_PartLevel_tt_%d", RType[ij].Data(), trg[ig].Data(), trigRangeLow);
			Pois_hist_RJ[ig] = MakePois(f1, name);
			name = Form("%s recoil jets histogram for %s at %d GeV/c; p_{T}, GeV/c; Counts", trg[ig].Data(), RType[ij].Data(), trigRangeLow);
			Pois_hist_RJ[ig]->SetTitle(name);
			Pois_hist_RJ[ig]->Write();

			name = Form("fhRecoilJetPhi_%s_%s_PartLevel_tt_%d", RType[ij].Data(), trg[ig].Data(), trigRangeLow);
			TH2D* hphi = (TH2D*) f1->Get(name);
			hphi->Write();

			name = Form("Norm_fhRecoilJetPt_%s_%s_PartLevel_tt_%d", RType[ij].Data(), trg[ig].Data(), trigRangeLow);
			TH1D* NormHist = (TH1D*) Pois_hist_RJ[ig]->Clone();
			NormHist->SetName(name);
			NormHist->Scale(1/integral);
			name = Form("%s normalized per TT recoil jets histogram for %s at %d GeV/c; p_{T}, GeV/c; Normalized per TT yield", trg[ig].Data(), RType[ij].Data(), trigRangeLow);
			NormHist->SetTitle(name);
			NormHist->Write();


		}
	}

	name = Form("Norm_fhRecoilJetPt_OO_MB_PartLevel_tt_%d", trigRangeLow);
	TH1D* histo_OO = (TH1D*) outFile->Get(name);
	histo_OO->SetDirectory(0);
	histo_OO->SetMarkerColor(2);
	histo_OO->SetLineColor(2);

	name = Form("Norm_fhRecoilJetPt_pp_MB_PartLevel_tt_%d", trigRangeLow);
	TH1D* histo_pp = (TH1D*) outFile->Get(name);
	histo_pp->SetDirectory(0);
	histo_pp->SetMarkerColor(1);
	histo_pp->SetLineColor(1);

	name = Form("canv_norm_per_TT_%d", trigRangeLow);
	TCanvas* c = new TCanvas("canv_norm_per_TT", name, 0., 0., 1000., 800.);
	c->cd();
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);
	gPad->SetLogy();
	histo_OO->Draw();
	histo_pp->Draw("same");
	gPad->Modified();
	gPad->Update();

	TPaveText *t = new TPaveText(0.05, 0.93, 0.95, 1.0, "brNDC");
	name = Form("MB normalized per TT recoil jets histogram for OO and pp at %d GeV/c", trigRangeLow);
	t->AddText(name);
	t->Draw();

	TLegend *leg_norm;
	leg_norm = new TLegend(0.4,0.6,0.95,0.95," ","brNDC");
	leg_norm->SetFillStyle(0); leg_norm->SetBorderSize(0); leg_norm->SetTextSize(0.03);
	leg_norm->AddEntry((TObject*) histo_OO, "OO","l");
	leg_norm->AddEntry((TObject*) histo_pp, "pp","l");
	leg_norm->Draw();

	SavePNGandEPS(c, 0); //save as image

	outFile->Close();
}

vector<TH1D*> MakeVectorHist(vector<TH1D*>& hist_vector, TString name, const Int_t& trigRangeLow_1){

	map<Int_t, Int_t> trigRanges = {{6, 7}, {12, 20}, {20, 30}};

	TFile* f1 = TFile::Open(name, "READ");
	cout << 3;

	TString name_newFile = Form("../TT-%d_%d/Normalized_by_tt_%d.root", trigRangeLow_1, trigRanges.at(trigRangeLow_1), trigRangeLow_1);
	TFile *nfile = new TFile(name_newFile, "RECREATE");
	nfile->Close();
	cout << 4;

	vector<Double_t> integr_1;
	integr_1.resize(2);
	Double_t luminosity = 4e6; //4 nb^-1 -> 4e6 mb^-1;
	Double_t luminosity_pp = 3e9;
	Int_t A = 16; //oxygen mass in amu
	Double_t factorOO = A * A * luminosity;
	Double_t integral = 0;
	Double_t integralTT = 0;

	//get scaled recoil jet spectra
	//get integral from trigger track spectra
	for(Int_t ig = kMB; ig< kTRIG; ig++){
		for(Int_t ij = kOO; ij< ktr; ij++){
			name = Form("hTT_%s_%s_PartLevel_tt_%d", RType[ij].Data(), trg[ig].Data(), trigRangeLow_1);
			TH1D* htt = (TH1D*) f1->Get(name);
			if(!htt){
				cout << "Wrong TT_Range for this file!" << trg[ig].Data() << 1 << endl;
				return {};
					 }
			integr_1[ig] = htt->Integral();

			//scale recoil jet spectrum to 1/integral
			name = Form("fhRecoilJetPt_%s_%s_PartLevel_tt_%d", RType[ij].Data(), trg[ig].Data(), trigRangeLow_1);
			TH1D* hpt = (TH1D*) f1->Get(name);
			if(!hpt){
				cout << "Wrong TT_Range for this file!" << trg[ig].Data() << 2 << endl;
				return {};
					 }

			TH1D* Scaled_hpt = (TH1D*) hpt->Clone();
			Scaled_hpt->SetDirectory(0);
			Scaled_hpt->Scale(1/integr_1[ig]);
			name = Form("Scaled_RecoilJetPt_%s_%s_PartLevel_tt_%d", RType[ij].Data(), trg[ig].Data(), trigRangeLow_1);
			Scaled_hpt->SetName(name);
			name = Form("%s normalized per TT recoil jets histogram for %s at %d GeV/c; p_{T}, GeV/c; Normalized per TT yield", trg[ig].Data(), RType[ij].Data(), trigRangeLow_1);
			Scaled_hpt->SetTitle(name);


			name_newFile = Form("../TT-%d_%d/Normalized_by_tt_%d.root", trigRangeLow_1, trigRanges.at(trigRangeLow_1), trigRangeLow_1);
			nfile = TFile::Open(name_newFile, "UPDATE");
			Scaled_hpt->Write();
			nfile->Close();

			hist_vector.push_back(Scaled_hpt);

			delete htt;
			delete hpt;
			delete Scaled_hpt;
		}
	}
	f1->Close();
	return hist_vector;
}

Double_t appr_func(Double_t* x, Double_t* par) {
	Double_t slp = 1.;
	if (par[1] != 0) { slp = par[1]; }
	else {slp = 1.; }
	Double_t fitval = par[0]*TMath::Exp(-(x[0] + par[2])/slp);
	return fitval;
}



void CalculateAQ(Double_t sigma) {
	Double_t mean = 0;
	Double_t cn = 1;
	TCanvas* c = new TCanvas("canv_gaus", "gaus", 0., 0., 800., 800.);
	 TF1 *g = new TF1("g","gaus",-sigma*10,sigma*10);
	g->SetParameters(cn, mean, sigma);
	Int_t np = 100;
	double* x = new double[np];
	double* w = new double[np];
	Double_t stot = g->IntegralFast(np, x, w, -sigma*10, sigma*10);
	Double_t si = 1;
	Double_t bnd = 0.;
	Double_t step = sigma/50000;
	while (si/stot > 0.1) {
		si = g->IntegralFast(np, x, w, bnd, sigma*10);
		bnd += step;
	}
	cout << stot << " " << si << " " << si/stot << endl;
	cout << "Boundary alpha: " << bnd << "; c: " << bnd/sigma << endl;
	c->cd();
	g->Draw();
}
