#include "TH1D.h"
#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TPad.h"
#include "TPaveText.h"

#include "ProcFunctions.h"

#include <iostream>
#include <vector>
using namespace std;
using std::cout;
using std::endl;

void SetCanvas(TCanvas* c);
void SetHist(TH1* h,TString titx, TString tity);
//void SavePNGandEPS(TCanvas* mycanv, bool isEPS);

Int_t Draw(){
	gROOT->Reset();
	map<Int_t, Int_t> trigRanges = {{6, 7}, {12, 20}, {20, 30}};
	
	map<Int_t, vector<TH1D>> histomap;
	histomap[6];
	histomap[12];
	histomap[20];
	for (auto& item : histomap) {
		item.second.resize(5);
	}
	
	//MAP OF HISTOGRAMS
	//KEY: TT = 
	//		6			12			20
	//VECTOR CONSTITUENTS:
	//0 = XSECT SPECTRUM WITH TT
	//1 = PP HISTOGRAM IN COUNTS
	//2 = OO HISTOGRAM IN COUNTS
	//3 = PP HISTOGRAM NORMALIZED PER TRIGGER TRACKS INTEGRAL
	//4 = OO HISTOGRAM NORMALIZED PER TRIGGER TRACKS INTEGRAL

	vector<TH1D*> DRhisto;
	
	//VECTOR OF DELTA_RECOIL HISTOGRAMS
	//0 = DELTA RECOIL FOR PP AT 6-7 && 12-20
	//1 = DELTA RECOIL FOR OO AT 6-7 && 12-20
	//2 = RATIO OF DELTA RECOIL FOR PP AND OO AT 6-7 && 12-20
	TString name = "";
	for (const pair<const int, const int>& item : trigRanges){
		Int_t ttLow = item.first;
		name = Form("../TT-%d_%d/Res_tt_%d.root", ttLow, trigRanges.at(ttLow), ttLow);
		TFile *f11 = TFile::Open(name,"READ");
		if(!f11) return 20; 

		//READ Xsect HISTOGRAM 
		name = Form("fhRecoilJetPt_MB_PartLevel_tt_%d", ttLow);
		TH1D*  RJSp_Xs0 = (TH1D*) f11->Get(name);
		TH1D* RJSp_Xs = (TH1D*) RJSp_Xs0->Clone();
		RJSp_Xs->SetDirectory(0);
		histomap.at(ttLow)[0] = (*RJSp_Xs);
		if(!RJSp_Xs) return 21; 
		f11->Close();

		name = Form("../TT-%d_%d/Res_pois_tt_%d.root", ttLow, trigRanges.at(ttLow), ttLow);
		TFile *f12 = TFile::Open(name,"READ");
		if(!f12) return 20; 

		//READ counts pp HISTOGRAM 
		name = Form("fhRecoilJetPt_pp_MB_PartLevel_tt_%d", ttLow);   
		TH1D*  RJSp_Cpp0 = (TH1D*) f12->Get(name);
		TH1D* RJSp_Cpp = (TH1D*) RJSp_Cpp0->Clone();
		RJSp_Cpp->SetDirectory(0);
		histomap.at(ttLow)[1] = (*RJSp_Cpp);
		if(!RJSp_Cpp) return 21; 

		//READ counts OO HISTOGRAM 
		name = Form("fhRecoilJetPt_OO_MB_PartLevel_tt_%d", ttLow);   
		TH1D*  RJSp_COO0 = (TH1D*) f12->Get(name);
		TH1D* RJSp_COO = (TH1D*) RJSp_COO0->Clone();
		RJSp_COO->SetDirectory(0);
		histomap.at(ttLow)[2] = (*RJSp_COO);
		if(!RJSp_COO) return 21;

		//READ normalized pp HISTOGRAM 
		name = Form("Norm_fhRecoilJetPt_pp_MB_PartLevel_tt_%d", ttLow);   
		TH1D*  RJSp_Npp0 = (TH1D*) f12->Get(name);
		TH1D* RJSp_Npp = (TH1D*) RJSp_Npp0->Clone();
		RJSp_Npp->SetDirectory(0);
		histomap.at(ttLow)[3] = (*RJSp_Npp);
		if(!RJSp_Npp) return 21; 

		//READ normalized OO HISTOGRAM 
		name = Form("Norm_fhRecoilJetPt_OO_MB_PartLevel_tt_%d", ttLow);   
		TH1D*  RJSp_NOO0 = (TH1D*) f12->Get(name);
		TH1D* RJSp_NOO = (TH1D*) RJSp_NOO0->Clone();
		RJSp_NOO->SetDirectory(0);
		histomap.at(ttLow)[4] = (*RJSp_NOO);
		if(!RJSp_NOO) return 21; 
		f12->Close();
	}

	name = Form("../DeltaRecoil_tt_6-7_tt_12-20.root");
	TFile *f13 = TFile::Open(name,"READ");
	if(!f13) return 20; 
	
	//READ Delta recoil 6-7 && 12-20 HISTOGRAM for pp 
	name = Form("Delta_RecoilJetPt_pp_MB_PartLevel_tt_6-7_tt_12-20");
	TH1D*  DRJSp_pp_612 = (TH1D*) f13->Get(name);
	DRhisto.push_back(DRJSp_pp_612);
	if(!DRJSp_pp_612) return 21; 
	
	//READ Delta recoil 6-7 && 12-20 HISTOGRAM for OO
	name = Form("Delta_RecoilJetPt_OO_MB_PartLevel_tt_6-7_tt_12-20");
	TH1D*  DRJSp_OO_612 = (TH1D*) f13->Get(name);
	DRhisto.push_back(DRJSp_OO_612);
	if(!DRJSp_OO_612) return 21; 
	
	name = Form("MB_delta_recoil_TT_%d_%d", 6, 12);
	TCanvas* c2 = new TCanvas("MB_delta_recoil_canv", name, 0., 0., 1000., 800.);
	c2->cd(0);
	gPad->SetLogy();
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	DRJSp_pp_612->SetDirectory(0);
	DRJSp_pp_612->SetLineColor(1);
	DRJSp_pp_612->SetMarkerColor(1);
	DRJSp_pp_612->Draw();
	gPad->Modified(); 
	gPad->Update();
	DRJSp_OO_612->SetDirectory(0);
	DRJSp_OO_612->SetLineColor(2);
	DRJSp_OO_612->SetMarkerColor(2);
	DRJSp_OO_612->Draw("same");
	gPad->Modified(); 
	gPad->Update();
	
	TPaveText *t = new TPaveText(0.05, 0.93, 0.95, 1.0, "brNDC");
	name = Form("MB #Delta_{recoil} histogram for pp and OO at TT p_{T} ranges %d-%d && %d-%d GeV/c", 
						6, 7, 12, 20);
	t->AddText(name);
	t->Draw();
	
	TLegend *leg_T1;
	leg_T1 = new TLegend(0.4,0.6,0.95,0.95," ","brNDC");
	leg_T1->SetFillStyle(0); leg_T1->SetBorderSize(0); leg_T1->SetTextSize(0.03);
	leg_T1->AddEntry((TObject*) DRJSp_OO_612, "OO","l");
	leg_T1->AddEntry((TObject*) DRJSp_pp_612, "pp","l");
	leg_T1->Draw();
	
	SavePNGandEPS(c2, 0);
	f13->Close();
	
	
	
	

		//----------------------------------------------------------
		/*gStyle->SetOptTitle(0);
		gStyle->SetOptStat(0);
		TCanvas *c[10];
		TLegend *leg;
		Int_t io = 0;

		//DRAW CAVAS WHERE ONE COMAPARES BOTH HISTOGRAMS
		c[io] = new TCanvas(Form("c%d",io), "JetCrossSections",0,0,600,500 ); 
		SetCanvas((TCanvas*) c[io]);
		c[io]->cd()->SetLogy(); 

		leg = new TLegend(0.5,0.6,0.95,0.95," ","brNDC");  //this will be legend
		leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.04);
		leg->AddEntry((TObject*) 0, "pp #sqrt{#it{s}} = 13 TeV","");
		leg->AddEntry((TObject*) 0, "anti-#it{k}_{T} #it{R} = 0.4","");

		SetHist((TH1*) hard, "#it{p}_{T,ch jet} (GeV/#it{c})", "cross section (mb)");
		hard->SetLineColor(2);
		soft->SetLineColor(4);

		leg->AddEntry((TObject*) hard, "hard bins","l");
		leg->AddEntry((TObject*) soft, "minimum bias","l");

		hard->Draw(); //here you draw the first histo
		soft->Draw("same"); //here you 

		leg->Draw();
		io++;


		//Print out commands for figure printout in terminal
		SavePNGandEPS((TCanvas**) c, io);*/
	
	name = "canvas_total_graphs";
	TCanvas* c = new TCanvas("canvas_total_graphs", name, 0., 0., 1000., 1000.);
	c->Divide(3,5);
	c->cd(1);
	int i = 1;
	for (auto& item: histomap) {
		for (auto& graph: item.second){
			TH1D* GraphToPlot = (TH1D*) graph.Clone();
			c->cd(i);
			gPad->SetLogy();
			GraphToPlot->Draw();
			gPad->Modified(); 
			gPad->Update();
			i++;
			//delete GraphToPlot;
		}
	}
	SavePNGandEPS(c, 0);
	//DRAW XSECTION; SMEARED PP AND OO SPECTRA; NORMALIZED PP AND OO SPECTRA
	vector<TCanvas*> canv_storage;
	for (size_t pos = 0; pos < 5; pos++){
		TString canv_name = Form("canvas_%ld", pos);
		TCanvas* c1 = new TCanvas(canv_name, "canvas", 0., 0., 1000., 800.);
		
		gPad->SetLogy();
		TH1D* GraphToPlot = (TH1D*)histomap.at(6).at(pos).Clone();
		GraphToPlot->SetMarkerColor(1);
		GraphToPlot->SetLineColor(1);
		gStyle->SetOptStat(0);
		gStyle->SetOptFit(0);
		GraphToPlot->Draw();
		gPad->Modified(); 
		gPad->Update();
		
		TH1D* GraphToPlot2 = (TH1D*)histomap.at(12).at(pos).Clone();
		GraphToPlot2->SetMarkerColor(2);
		GraphToPlot2->SetLineColor(2);
		GraphToPlot2->Draw("same");
		gPad->Modified(); 
		gPad->Update();
		
		TH1D* GraphToPlot3 = (TH1D*)histomap.at(20).at(pos).Clone();
		GraphToPlot3->SetMarkerColor(4);
		GraphToPlot3->SetLineColor(4);
		GraphToPlot3->Draw("same");
		gPad->Modified(); 
		gPad->Update();
		
		TPaveText *t = new TPaveText(0.05, 0.93, 0.95, 1.0, "brNDC");
		switch (pos) {
			case 0: { name = Form("MB recoil jets histogram (Xsection)");
				break;}
			case 1: { name = Form("MB recoil jets histogram for pp");
				break;
			}
			case 2: { name = Form("MB recoil jets histogram for OO");
				break;
			}
			case 3: { name = Form("Normalized per TT integral MB recoil jets histogram for pp");
				break;
			}
			case 4: { name = Form("Normalized per TT integral MB recoil jets histogram for OO");
				break;
			}
			default: { name = Form("Unknown histogram...");
				break;
			}
		}
		c1->SetTitle(name);
		t->AddText(name);
		t->Draw();
		
		TLegend *leg;
		leg = new TLegend(0.5,0.6,0.95,0.95," ","brNDC");
		leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.04);
		//leg->AddEntry((TObject*) 0, "pp #sqrt{#it{s}} = 13 TeV","");
		//leg->AddEntry((TObject*) 0, "anti-#it{k}_{T} #it{R} = 0.4","");
		
		leg->AddEntry((TObject*) GraphToPlot, "TT = 6-7 GeV/c","l");
		leg->AddEntry((TObject*) GraphToPlot2, "TT = 12-20 GeV/c","l");
		leg->AddEntry((TObject*) GraphToPlot3, "TT = 20-30 GeV/c","l");
		
		leg->Draw();
		SavePNGandEPS(c1, 0);
		canv_storage.push_back(c1);
	}
	
	
/*	TCanvas* c1 = new TCanvas("canv2", "canvas", 0., 0., 600., 800.);
	c1->cd(0);
	gPad->SetLogy();
	TH1D* GraphToPlot = (TH1D*)histomap.at(12).at(2).Clone();
	GraphToPlot->SetMarkerColor(1);
	GraphToPlot->SetLineColor(1);
	GraphToPlot->Draw();
	gPad->Modified(); 
	gPad->Update();
	TH1D* GraphToPlot2 = (TH1D*)histomap.at(6).at(2).Clone();
	GraphToPlot2->SetMarkerColor(2);
	GraphToPlot2->SetLineColor(2);
	GraphToPlot2->Draw("same");
	gPad->Modified(); 
	gPad->Update();
	TH1D* GraphToPlot3 = (TH1D*)histomap.at(20).at(2).Clone();
	GraphToPlot3->SetMarkerColor(4);
	GraphToPlot3->SetLineColor(4);
	GraphToPlot3->Draw("same");
	gPad->Modified(); 
	gPad->Update();*/
	
		return 11;
}

//_____________________________________________________________________


void SetHist(TH1* h,TString titx, TString tity){

   h->GetXaxis()->SetTitle(titx.Data());
   h->GetYaxis()->SetTitle(tity.Data());
   h->GetXaxis()->SetTitleSize(0.05);
   h->GetYaxis()->SetTitleSize(0.05);
   h->GetXaxis()->SetLabelSize(0.04);
   h->GetYaxis()->SetLabelSize(0.04);

   h->GetYaxis()->SetTitleOffset(1.3);
   h->GetXaxis()->SetTitleOffset(1.2);

}

//_____________________________________________________________________

void SetCanvas(TCanvas* c){
   c->SetLeftMargin(0.17);
   c->SetBottomMargin(0.14);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetTickx();
   c->SetTicky();
}


//_____________________________________________________________________


