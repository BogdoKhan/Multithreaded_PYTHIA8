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
#include "TGraph.h"

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
		name = Form("; p_{T}, GeV/c; #sigma, mb");
		fhTTHPartLevel[ig]->SetTitle(name);
		name = Form("; p_{T}, GeV/c; #sigma, mb");
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
	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.15);
	gStyle->SetPadRightMargin(0.05);
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
	Double_t factor_pO = A * luminosity;

	Double_t integral = 0;

	for(Int_t ig = kMB; ig< kTRIG; ig++){
		name = Form("hTT_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		TH1D* htt = (TH1D*) f1->Get(name);
		TH1D* htt_pp = (TH1D*) htt->Clone();
		TH1D* htt_pO = (TH1D*) htt->Clone();

//OO
		name = Form("hTT_OO_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		htt = Scaler(htt, name, factorOO);
		name = Form("; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Counts");
		htt->SetTitle(name);

		htt->Write();
		integral = htt->Integral()/factorOO;
		cout << "OO " << integral << endl;

//pp
		name = Form("hTT_pp_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		htt_pp = Scaler(htt_pp, name, luminosity_pp);
		name = Form("; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Counts");
		htt_pp->SetTitle(name);
		htt_pp->Write();
		integral = htt_pp->Integral()/luminosity_pp;
		cout << "pp " << integral << endl;

//pO
		name = Form("hTT_pO_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		htt_pO = Scaler(htt_pO, name, factor_pO);
		name = Form("; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Counts");
		htt_pO->SetTitle(name);
		htt_pO->Write();
		integral = htt_pO->Integral()/factor_pO;
		cout << "pO " << integral << endl;


		name = Form("fhRecoilJetPt_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		TH1D* hpt = (TH1D*) f1->Get(name);
		TH1D* hpt_pp = (TH1D*) hpt->Clone();
		TH1D* hpt_pO = (TH1D*) hpt->Clone();

		name = Form("fhRecoilJetPt_OO_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		hpt = Scaler(hpt, name, factorOO);
		name = Form("; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Counts");
		hpt->SetTitle(name);
		hpt->Write();


		name = Form("fhRecoilJetPt_pp_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		hpt_pp = Scaler(hpt_pp, name, luminosity_pp);
		name = Form("; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Counts");
		hpt_pp->SetTitle(name);
		hpt_pp->Write();

		name = Form("fhRecoilJetPt_pO_%s_PartLevel_tt_%d", trg[ig].Data(), trigRangeLow);
		hpt_pO = Scaler(hpt_pO, name, factor_pO);
		//name = Form("Unsmeared %s recoil jets histogram for pO at %d GeV/c; p_{T}, GeV/c; Counts", trg[ig].Data(), trigRangeLow);
		hpt_pO->SetTitle("; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Counts");
		hpt_pO->Write();


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
	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.15);
	gStyle->SetPadRightMargin(0.05);
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
			name = Form("; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Counts");
			Pois_hist_TT[ig]->SetTitle(name);
			Pois_hist_TT[ig]->Write();
			integral = Pois_hist_TT[ig]->Integral();

			name = Form("fhRecoilJetPt_%s_%s_PartLevel_tt_%d", RType[ij].Data(), trg[ig].Data(), trigRangeLow);
			Pois_hist_RJ[ig] = MakePois(f1, name);
			name = Form("; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Counts");
			Pois_hist_RJ[ig]->SetTitle(name);
			Pois_hist_RJ[ig]->Write();

			name = Form("fhRecoilJetPhi_%s_%s_PartLevel_tt_%d", RType[ij].Data(), trg[ig].Data(), trigRangeLow);
			TH2D* hphi = (TH2D*) f1->Get(name);
			hphi->Write();

			name = Form("Norm_fhRecoilJetPt_%s_%s_PartLevel_tt_%d", RType[ij].Data(), trg[ig].Data(), trigRangeLow);
			TH1D* NormHist = (TH1D*) Pois_hist_RJ[ig]->Clone();
			NormHist->SetName(name);
			NormHist->Scale(1/integral);
			name = Form("; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Normalized per TT yield");
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
	histo_OO->SetTitleOffset(1.7, "x");
	histo_pp->Draw("same");
	gPad->Modified();
	gPad->Update();

	// TPaveText *t = new TPaveText(0.05, 0.93, 0.95, 1.0, "brNDC");
	// name = Form("MB normalized per TT recoil jets histogram for OO and pp at %d GeV/c", trigRangeLow);
	// t->AddText(name);
	// t->Draw();

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
	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.15);
	gStyle->SetPadRightMargin(0.05);

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
			name = Form("; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Normalized per TT yield");
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

void ScaleTG(Double_t c1, Option_t *option, TGraph* tg)
{
   TString opt = option; opt.ToLower();
   if (opt.Contains("x")) {
      for (Int_t i=0; i<tg->GetN(); i++)
         tg->GetX()[i] *= c1;
   }
   if (opt.Contains("y")) {
      for (Int_t i=0; i<tg->GetN(); i++)
         tg->GetY()[i] *= c1;
   }
}

void CalculateAQ(Double_t sigma) {

	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.15);
	gStyle->SetPadRightMargin(0.05);

	Double_t mean = 0; //build gaussian with given sigma and 0 mean
	Double_t cn = 1;
	TCanvas* c = new TCanvas("canv_gaus", "gaus", 0., 0., 800., 800.);
	 TF1 *g = new TF1("g","gaus",-sigma*5,sigma*5);
	g->SetParameters(cn, mean, sigma);
	Int_t np = 100;
	double* x = new double[np]; //calculation of integral under gaussian
	double* w = new double[np];
	Double_t stot = g->IntegralFast(np, x, w, -sigma*5, sigma*5);
	Double_t si = 1;
	Double_t bnd = 0.;
	Double_t step = sigma/10000;
	while (si/stot > 0.1) {	//step-by step evaluation of one-sided integral
		si = g->IntegralFast(np, x, w, bnd, sigma*5);	//between moving boundary and gaussian right boundary
		bnd += step;
	}
	cout << stot << " " << si << " " << si/stot << endl; //total area under gaussian; area between AQ and
	cout << "Boundary alpha: " << bnd << "; c: " << bnd/sigma << endl;//right boundary; their ratio ~ 0.1
	c->cd();																													//abs value of boundary and in value of sigmas
	g->SetTitle("; #it{p}_{T}, #frac{GeV}{#it{c}}; Gaussian value");
	g->GetXaxis()->SetRange(-sigma*5, sigma*5);

	g->Draw();
	TF1* g1 = new TF1("g1", "gaus", -sigma*5, bnd);
	g1->SetParameters(cn, mean, sigma);
	g1->SetFillColor(kRed);
//	g1->SetFillColorAlpha(0.3);
	g1->SetFillStyle(3001);
	g1->Draw("SAME FC");

	TLine* unity = new TLine(bnd, 0., bnd, g->Eval(bnd));
	unity->SetLineStyle(2);
	unity->Draw("same");

	TLegend *leg_1;
	leg_1 = new TLegend(0.5,0.8,0.9,0.9," ","brNDC");
	leg_1->SetFillStyle(0); leg_1->SetBorderSize(0); leg_1->SetTextSize(0.03);
	leg_1->AddEntry((TObject*) 0, Form("Z(CL 90%%) = %.3f#sigma", bnd/sigma),"");
	leg_1->AddEntry((TObject*) 0, Form("#alpha-quantile: %.3f GeV/c", bnd),"");
	leg_1->Draw("same");
	g->GetXaxis()->SetRangeUser(-5*sigma, 5*sigma);

	TCanvas* c1 = new TCanvas("canv_gaus_CDF", "gaus_CDF", 0., 0., 800., 800.);
	c1->cd();
	TGraph* tg = ((TGraph*) g->DrawIntegral());
	tg->SetTitle("; #it{p}_{T}, #frac{GeV}{#it{c}}; Gaussian CDF value");
	ScaleTG(1/stot, "y", tg);
	tg->GetXaxis()->SetRangeUser(-sigma*5, sigma*5);
	tg->Draw();
	TLine* unity_tg = new TLine(bnd, 0., bnd, tg->Eval(bnd));
	unity_tg->SetLineStyle(2);
	unity_tg->Draw("same");
	TLine* val_tg = new TLine(-5*sigma, tg->Eval(bnd), bnd, tg->Eval(bnd));
	val_tg->SetLineStyle(2);
	val_tg->Draw("same");

	TLegend *leg_2;
	leg_2 = new TLegend(0.1,0.6,0.4,0.5," ","brNDC");
	leg_2->SetFillStyle(0); leg_2->SetBorderSize(0); leg_2->SetTextSize(0.03);
	leg_2->AddEntry((TObject*) 0, Form("Z(CL 90%%) = %.3f#sigma", bnd/sigma),"");
	leg_2->AddEntry((TObject*) 0, Form("#alpha-quantile: %.3f GeV/c", bnd),"");
	leg_2->Draw("same");

}
