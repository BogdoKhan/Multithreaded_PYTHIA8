#include "MergeHist.cc"

void protoxy_Histos(){

	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.15);
	gStyle->SetPadRightMargin(0.05);

	name = Form("5_502_Res_scaled_tt_6.root");
	TFile *inFile0 = new TFile(name, "READ");

	name = Form("po_tunes.root");
	TFile *outFile = new TFile(name, "RECREATE");
	outFile->cd();

	name = Form("hTT_pp_MB_PartLevel_tt_6");
	TH1D* htt_5502 = (TH1D*) inFile0->Get(name);
	name = Form("5_502_hTT_pp_MB_PartLevel_tt_6");
	htt_5502->SetTitle(name);
	Double_t integral = htt_5502->Integral();

	name = Form("fhRecoilJetPt_pp_MB_PartLevel_tt_6");
	TH1D* hpt_5502 = (TH1D*) inFile0->Get(name);
	name = Form("5_502_RJ_pp_MB_PartLevel_tt_6");
	hpt_5502->SetTitle(name);
	hpt_5502 = Scaler(hpt_5502, name, 1/integral);
	hpt_5502->Write();
	//inFile0->Close();
	//----------------------------------------
	name = Form("5_502_Res_scaled_tt_12.root");
	TFile *inFile1 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pp_MB_PartLevel_tt_12");
	TH1D* htt_5502_1 = (TH1D*) inFile1->Get(name);
	name = Form("5_502_hTT_pp_MB_PartLevel_tt_12");
	htt_5502_1->SetTitle(name);
	integral = htt_5502_1->Integral();

	name = Form("fhRecoilJetPt_pp_MB_PartLevel_tt_12");
	TH1D* hpt_5502_1 = (TH1D*) inFile1->Get(name);
	name = Form("5_502_RJ_pp_MB_PartLevel_tt_12");
	hpt_5502_1->SetTitle(name);
	hpt_5502_1 = Scaler(hpt_5502_1, name, 1/integral);
	hpt_5502_1->Write();
	//inFile1->Close();
	//----------------------------------------
	TH1D* nhpt_5502 = (TH1D*) hpt_5502->Clone("5_502_NRJ_pp");
	nhpt_5502->Add(hpt_5502_1, hpt_5502, 1, -1);
	name = Form("5_502_NRJ_pp");
	nhpt_5502->SetTitle(name);
	nhpt_5502->Write();
	//------------------------------------------
	name = Form("5_pO_Res_scaled_tt_6.root");
	TFile *inFile2 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pO_MB_PartLevel_tt_6");
	TH1D* htt_5pO = (TH1D*) inFile2->Get(name);
	name = Form("5_pO_hTT_pO_MB_PartLevel_tt_6");
	htt_5pO->SetTitle(name);
	integral = htt_5pO->Integral();

	name = Form("fhRecoilJetPt_pO_MB_PartLevel_tt_6");
	TH1D* hpt_5pO = (TH1D*) inFile2->Get(name);
	name = Form("5_pO_RJ_pO_MB_PartLevel_tt_6");
	hpt_5pO->SetTitle(name);
	hpt_5pO = Scaler(hpt_5pO, name, 1/integral);
	hpt_5pO->Write();
	//inFile2->Close();
	//----------------------
	name = Form("5_pO_Res_scaled_tt_12.root");
	TFile *inFile3 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pO_MB_PartLevel_tt_12");
	TH1D* htt_5pO_1 = (TH1D*) inFile3->Get(name);
	name = Form("5_pO_hTT_pO_MB_PartLevel_tt_12");
	htt_5pO_1->SetTitle(name);
	integral = htt_5pO_1->Integral();

	name = Form("fhRecoilJetPt_pO_MB_PartLevel_tt_12");
	TH1D* hpt_5pO_1 = (TH1D*) inFile3->Get(name);
	name = Form("5_pO_RJ_pO_MB_PartLevel_tt_12");
	hpt_5pO_1->SetTitle(name);
	hpt_5pO_1 = Scaler(hpt_5pO_1, name, 1/integral);
	hpt_5pO_1->Write();
	//inFile3->Close();
	//------------------------------
	TH1D* nhpt_5pO = (TH1D*) hpt_5pO->Clone("5_pO_NRJ_pp");
	nhpt_5pO->Add(hpt_5pO_1, hpt_5pO, 1, -1);
	name = Form("5_pO_NRJ_pp");
	nhpt_5pO->SetTitle(name);
	nhpt_5pO->Write();
	//------------------------------------------
	TH1D* dnhpt_5 = (TH1D*) hpt_5pO->Clone("5_DNRJ_pp");
	dnhpt_5->Divide(nhpt_5pO, nhpt_5502, 1, 1);
	name = Form("5_DNRJ_pp");
	dnhpt_5->SetTitle(name);
	dnhpt_5->Write();
	//------------------------------------------
	name = Form("14_502_Res_scaled_tt_6.root");
	TFile *inFile4 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pp_MB_PartLevel_tt_6");
	TH1D* htt_14502 = (TH1D*) inFile4->Get(name);
	name = Form("14_502_hTT_pp_MB_PartLevel_tt_6");
	htt_14502->SetTitle(name);
	integral = htt_14502->Integral();

	name = Form("fhRecoilJetPt_pp_MB_PartLevel_tt_6");
	TH1D* hpt_14502 = (TH1D*) inFile4->Get(name);
	name = Form("14_502_RJ_pp_MB_PartLevel_tt_6");
	hpt_14502->SetTitle(name);
	hpt_14502 = Scaler(hpt_14502, name, 1/integral);
	hpt_14502->Write();
	//inFile4->Close();
	//----------------------------------------
	name = Form("14_502_Res_scaled_tt_12.root");
	TFile *inFile5 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pp_MB_PartLevel_tt_12");
	TH1D* htt_14502_1 = (TH1D*) inFile5->Get(name);
	name = Form("14_502_hTT_pp_MB_PartLevel_tt_12");
	htt_14502_1->SetTitle(name);
	integral = htt_14502_1->Integral();

	name = Form("fhRecoilJetPt_pp_MB_PartLevel_tt_12");
	TH1D* hpt_14502_1 = (TH1D*) inFile5->Get(name);
	name = Form("14_502_RJ_pp_MB_PartLevel_tt_12");
	hpt_14502_1->SetTitle(name);
	hpt_14502_1 = Scaler(hpt_14502_1, name, 1/integral);
	hpt_14502_1->Write();
	//inFile5->Close();
	//--------------------------------------------
	TH1D* nhpt_14502 = (TH1D*) hpt_14502->Clone("14_502_NRJ_pp");
	nhpt_14502->Add(hpt_14502_1, hpt_14502, 1, -1);
	name = Form("14_502_NRJ_pp");
	nhpt_14502->SetTitle(name);
	nhpt_14502->Write();
	//------------------------------------------
	name = Form("14_pO_Res_scaled_tt_6.root");
	TFile *inFile6 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pO_MB_PartLevel_tt_6");
	TH1D* htt_14pO = (TH1D*) inFile6->Get(name);
	name = Form("14_pO_hTT_pO_MB_PartLevel_tt_6");
	htt_14pO->SetTitle(name);
	integral = htt_14pO->Integral();

	name = Form("fhRecoilJetPt_pO_MB_PartLevel_tt_6");
	TH1D* hpt_14pO = (TH1D*) inFile6->Get(name);
	name = Form("14_pO_RJ_pO_MB_PartLevel_tt_6");
	hpt_14pO->SetTitle(name);
	hpt_14pO = Scaler(hpt_14pO, name, 1/integral);
	hpt_14pO->Write();
	//inFile6->Close();
	//-----------------------------------
	name = Form("14_pO_Res_scaled_tt_12.root");
	TFile *inFile7 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pO_MB_PartLevel_tt_12");
	TH1D* htt_14pO_1 = (TH1D*) inFile7->Get(name);
	name = Form("14_pO_hTT_pO_MB_PartLevel_tt_12");
	htt_14pO_1->SetTitle(name);
	integral = htt_14pO_1->Integral();

	name = Form("fhRecoilJetPt_pO_MB_PartLevel_tt_12");
	TH1D* hpt_14pO_1 = (TH1D*) inFile7->Get(name);
	name = Form("14_pO_RJ_pO_MB_PartLevel_tt_12");
	hpt_14pO_1->SetTitle(name);
	hpt_14pO_1 = Scaler(hpt_14pO_1, name, 1/integral);
	hpt_14pO_1->Write();
	//inFile7->Close();
	//---------------------------------
	TH1D* nhpt_14pO = (TH1D*) hpt_14pO->Clone("14_pO_NRJ_pp");
	nhpt_14pO->Add(hpt_14pO_1, hpt_14pO, 1, -1);
	name = Form("14_pO_NRJ_pp");
	nhpt_14pO->SetTitle(name);
	nhpt_14pO->Write();
	//------------------------------------------
	TH1D* dnhpt_14 = (TH1D*) hpt_14pO->Clone("14_DNRJ_pp");
	dnhpt_14->Divide(nhpt_14pO, nhpt_14502, 1, 1);
	name = Form("14_DNRJ_pp");
	dnhpt_14->SetTitle(name);
	dnhpt_14->Write();
	//------------------------------------------
	name = Form("21_502_Res_scaled_tt_6.root");
	TFile *inFile8 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pp_MB_PartLevel_tt_6");
	TH1D* htt_21502 = (TH1D*) inFile8->Get(name);
	name = Form("21_502_hTT_pp_MB_PartLevel_tt_6");
	htt_21502->SetTitle(name);
	integral = htt_21502->Integral();

	name = Form("fhRecoilJetPt_pp_MB_PartLevel_tt_6");
	TH1D* hpt_21502 = (TH1D*) inFile8->Get(name);
	name = Form("21_502_RJ_pp_MB_PartLevel_tt_6");
	hpt_21502->SetTitle(name);
	hpt_21502 = Scaler(hpt_21502, name, 1/integral);
	hpt_21502->Write();
	//inFile8->Close();
	//-----------------------------------
	name = Form("21_502_Res_scaled_tt_12.root");
	TFile *inFile9 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pp_MB_PartLevel_tt_12");
	TH1D* htt_21502_1 = (TH1D*) inFile9->Get(name);
	name = Form("21_502_hTT_pp_MB_PartLevel_tt_12");
	htt_21502_1->SetTitle(name);
	integral = htt_21502_1->Integral();

	name = Form("fhRecoilJetPt_pp_MB_PartLevel_tt_12");
	TH1D* hpt_21502_1 = (TH1D*) inFile9->Get(name);
	name = Form("21_502_RJ_pp_MB_PartLevel_tt_12");
	hpt_21502_1->SetTitle(name);
	hpt_21502_1 = Scaler(hpt_21502_1, name, 1/integral);
	hpt_21502_1->Write();
	//inFile9->Close();
	//----------------------------------
	TH1D* nhpt_21502 = (TH1D*) hpt_21502->Clone("21_502_NRJ_pp");
	nhpt_21502->Add(hpt_21502_1, hpt_21502, 1, -1);
	name = Form("21_502_NRJ_pp");
	nhpt_21502->SetTitle(name);
	nhpt_21502->Write();
	//------------------------------------------
	name = Form("21_pO_Res_scaled_tt_6.root");
	TFile *inFile10 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pO_MB_PartLevel_tt_6");
	TH1D* htt_21pO = (TH1D*) inFile10->Get(name);
	name = Form("21_pO_hTT_pO_MB_PartLevel_tt_6");
	htt_21pO->SetTitle(name);
	integral = htt_21pO->Integral();

	name = Form("fhRecoilJetPt_pO_MB_PartLevel_tt_6");
	TH1D* hpt_21pO = (TH1D*) inFile10->Get(name);
	name = Form("21_pO_RJ_pO_MB_PartLevel_tt_6");
	hpt_21pO->SetTitle(name);
	hpt_21pO = Scaler(hpt_21pO, name, 1/integral);
	hpt_21pO->Write();
	//inFile10->Close();
	//---------------------------
	name = Form("21_pO_Res_scaled_tt_12.root");
	TFile *inFile11 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pO_MB_PartLevel_tt_12");
	TH1D* htt_21pO_1 = (TH1D*) inFile11->Get(name);
	name = Form("21_pO_hTT_pO_MB_PartLevel_tt_12");
	htt_21pO_1->SetTitle(name);
	integral = htt_21pO_1->Integral();

	name = Form("fhRecoilJetPt_pO_MB_PartLevel_tt_12");
	TH1D* hpt_21pO_1 = (TH1D*) inFile11->Get(name);
	name = Form("21_pO_RJ_pO_MB_PartLevel_tt_12");
	hpt_21pO_1->SetTitle(name);
	hpt_21pO_1 = Scaler(hpt_21pO_1, name, 1/integral);
	hpt_21pO_1->Write();
	//inFile11->Close();
	//-----------------------------
	TH1D* nhpt_21pO = (TH1D*) hpt_21pO->Clone("21_pO_NRJ_pp");
	nhpt_21pO->Add(hpt_21pO_1, hpt_21pO, 1, -1);
	name = Form("21_pO_NRJ_pp");
	nhpt_21pO->SetTitle(name);
	nhpt_21pO->Write();
	//------------------------------------------
	TH1D* dnhpt_21 = (TH1D*) hpt_21pO->Clone("21_DNRJ_pp");
	dnhpt_21->Divide(nhpt_21pO, nhpt_21502, 1, 1);
	name = Form("21_DNRJ_pp");
	dnhpt_21->SetTitle(name);
	dnhpt_21->Write();
	//------------------------------------------

	name = Form("DeltaRecoil_tt_6-7_tt_12-20.root");
	TFile *inFile12 = new TFile(name, "READ");
	outFile->cd();
	name = Form("Delta_RecoilJetPt_pO_MB_PartLevel_tt_6-7_tt_12-20");
	TH1D* drj_14 = (TH1D*) inFile12->Get(name);
	name = Form("Delta_RecoilJetPt_pO");
	drj_14->SetTitle(name);


	TF1* lintune = new TF1("lintune", "[0] + x * [1]", 0, 180);
	lintune->SetParameters(0.9, 0.002);
	lintune->SetParNames("Constant", "Slope");

	name = Form("Tunes");
	TCanvas* c2 = new TCanvas("MB_delta_recoil_canv", name, 0., 0., 1000., 800.);
	c2->cd(0);
	//gPad->SetLogy();
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	dnhpt_5->SetDirectory(0);
	dnhpt_5->SetLineColor(1);
	dnhpt_5->SetMarkerColor(1);

	dnhpt_5->SetTitle("");
	dnhpt_5->GetXaxis()->SetTitle("#it{p}_{T,jet}^{ch}");
    dnhpt_5->GetYaxis()->SetTitle("#frac{#Delta_{recoil_tune_{i}}^{6.37}}{#Delta_{recoil_tune_{i}}^{5.02}}  ");
	dnhpt_5->GetXaxis()->SetRangeUser(20., 50.);
	dnhpt_5->GetYaxis()->SetRangeUser(0.85, 1.25);
	dnhpt_5->Draw();
	gPad->Modified();
	gPad->Update();
	dnhpt_5->Fit("lintune","R","",20.,50.);
	TF1* fit5_l = dnhpt_5->GetFunction("lintune");
	fit5_l->SetLineColor(1);
	fit5_l->Draw("same");
	gPad->Modified();
	gPad->Update();

	dnhpt_14->SetDirectory(0);
	dnhpt_14->SetLineColor(2);
	dnhpt_14->SetMarkerColor(2);
	dnhpt_14->Draw("same");
	gPad->Modified();
	gPad->Update();
	dnhpt_14->Fit("lintune","R","",20.,50.);
	TF1* fit14_l = dnhpt_14->GetFunction("lintune");
	fit14_l->SetLineColor(2);
	fit14_l->Draw("same");
	gPad->Modified();
	gPad->Update();


	dnhpt_21->SetDirectory(0);
	dnhpt_21->SetLineColor(3);
	dnhpt_21->SetMarkerColor(3);
	dnhpt_21->Draw("same");
	gPad->Modified();
	gPad->Update();
	dnhpt_21->Fit("lintune","R","",20.,50.);
	TF1* fit21_l = dnhpt_21->GetFunction("lintune");
	fit21_l->SetLineColor(3);
	fit21_l->Draw("same");
	gPad->Modified();
	gPad->Update();

	TLegend *leg_T1;
	leg_T1 = new TLegend(0.4,0.6,0.95,0.95," ","brNDC");
	leg_T1->SetFillStyle(0); leg_T1->SetBorderSize(0); leg_T1->SetTextSize(0.03);
	leg_T1->AddEntry((TObject*) dnhpt_5, "Tune 5","l");
	leg_T1->AddEntry((TObject*) dnhpt_14, "Tune 14","l");
	leg_T1->AddEntry((TObject*) dnhpt_21, "Tune 21","l");
	leg_T1->Draw();

	SavePNGandEPS(c2, 0);

	TF1* func = new TF1("expoconst", appr_func, 0, 180, 3);
	func->SetParameters(1e-2, 2e1, 0.);
	func->SetParNames("Constant", "Slope", "Shift");
	func->SetParLimits(0, 1e-2, 1);
	func->FixParameter(2, 0.);

	//create canvas for exponential functions
	//here 14 tune spectrum at 5.02 TeV is scaled by prevoius fits
	//for different tunes, leading to "calculated 9 TeV spectrum"
	TCanvas* c4 = new TCanvas("MBd", "mbd", 0., 0., 1000., 800.);
	c4->cd(0);

	TH1D* shpt_5 = (TH1D*) nhpt_14502->Clone("5_ScaledTopO");
	shpt_5->SetLineColor(1);
	shpt_5->SetMarkerColor(1);
	shpt_5->Multiply(fit5_l, 1);
	shpt_5->GetXaxis()->SetRangeUser(20., 50.);
	shpt_5->Write();

	TH1D* shpt_14 = (TH1D*) nhpt_14502->Clone("14_ScaledTopO");
	shpt_14->SetLineColor(2);
	shpt_14->SetMarkerColor(2);
	shpt_14->Multiply(fit14_l, 1);
	shpt_14->GetXaxis()->SetRangeUser(20., 50.);
	shpt_14->GetYaxis()->SetMaxDigits(2);
	shpt_14->Write();

	TH1D* shpt_21 = (TH1D*) nhpt_14502->Clone("21_ScaledTopO");
	shpt_21->SetLineColor(3);
	shpt_21->SetMarkerColor(3);
	shpt_21->Multiply(fit21_l, 1);
	shpt_21->GetXaxis()->SetRangeUser(20., 50.);
	shpt_21->Write();

//as reference for fit, 9 TeV w/ 14 tune pO spectrum is taken
	cout << "======================TUNE 14 base: pO @ 9=======================" << endl;
	nhpt_14pO->Fit("expoconst","R","",20.,50.);
	//nhpt_14pO->Fit("expoconst","R","",20.,50.);
	TF1* fit_pl = nhpt_14pO->GetFunction("expoconst");
	Double_t const1 = fit_pl->GetParameter(0);
	Double_t slope = fit_pl->GetParameter(1);
	func->FixParameter(0, const1);
	func->ReleaseParameter(2);

	cout << "======================TUNE 14=======================" << endl;
	shpt_14->Fit("expoconst","R","",20.,50.);
	shpt_14->Draw();
	TF1* fit14 = shpt_14->GetFunction("expoconst");
	fit14->SetLineColor(2);
	fit14->SetLineWidth(1);
	fit14->Draw("same");


	cout << "======================TUNE 5=======================" << endl;
	shpt_5->Fit("expoconst","R0","",20.,50.);
	shpt_5->Draw("same");
	TF1* fit5 = shpt_5->GetFunction("expoconst");
	fit5->SetLineColor(1);
	fit5->SetLineWidth(1);
	fit5->Draw("same");

	cout << "======================TUNE 21=======================" << endl;
	shpt_21->Fit("expoconst","R0","",20.,50.);
	shpt_21->Draw("same");
	TF1* fit21 = shpt_21->GetFunction("expoconst");
	fit21->SetLineColor(3);
	fit21->SetLineWidth(1);
	fit21->Draw("same");

	TLegend *leg_T2;
	leg_T2 = new TLegend(0.4,0.6,0.95,0.95," ","brNDC");
	leg_T2->SetFillStyle(0); leg_T2->SetBorderSize(0); leg_T2->SetTextSize(0.03);
	leg_T2->AddEntry((TObject*) fit5, "Tune 5","l");
	leg_T2->AddEntry((TObject*) fit14, "Tune 14","l");
	leg_T2->AddEntry((TObject*) fit21, "Tune 21","l");
	leg_T2->Draw();

	shpt_14->GetXaxis()->SetTitle("#it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}");
    shpt_14->GetYaxis()->SetTitle("#Delta_{recoil, tune_{i}}^{6.37 TeV}(#it{p}_{T,jet}^{ch}), #left( #frac{GeV}{#it{c}} #right)^{-1}");
	shpt_14->SetTitle("");
}

TH1D* MakePois_pO(TFile* f1, const TString& name) {
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


	TString RTypepo[] = {"pO", "pp"};

void DoPoisSmearing_pO(Int_t tune, Int_t trigRangeLow){


	name = Form("%d_pO_Res_scaled_tt_%d.root", tune, trigRangeLow);
	TFile* f1 = TFile::Open(name, "READ");
	name = Form("%d_pO_Res_pois_tt_%d.root", tune, trigRangeLow);
	TFile *outFile = new TFile(name, "RECREATE");
	outFile->cd();

	TH1D* Pois_hist_TT[kTRIG];
	TH1D* Pois_hist_RJ[kTRIG];

	Int_t nbins = 0;
	TRandom3 gener;

	// Double_t luminosity = 4e6; //4 nb^-1 -> 4e6 mb^-1;
	// Double_t luminosity_pp = 3e9;
	// Int_t A = 16; //oxygen mass in amu
	// Double_t factorpO = A * luminosity;
	Double_t integral = 0;

	for(Int_t ig = kMB; ig< kTRIG; ig++){
		for(Int_t ij = kOO; ij< ktr; ij++){
			name = Form("hTT_%s_%s_PartLevel_tt_%d", RTypepo[ij].Data(), trg[ig].Data(), trigRangeLow);
			//Pois_hist_TT[ig] = MakePois(f1, name);
			TH1D* histo = (TH1D*) f1->Get(name);
			Pois_hist_TT[ig] = (TH1D*) histo->Clone();
			name = Form("; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Counts");
			Pois_hist_TT[ig]->SetTitle(name);
			Pois_hist_TT[ig]->Write();
			integral = Pois_hist_TT[ig]->Integral();

			name = Form("fhRecoilJetPt_%s_%s_PartLevel_tt_%d", RTypepo[ij].Data(), trg[ig].Data(), trigRangeLow);
			Pois_hist_RJ[ig] = MakePois(f1, name);
			name = Form(" ; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Counts");
			Pois_hist_RJ[ig]->SetTitle(name);
			Pois_hist_RJ[ig]->Write();

			name = Form("Norm_fhRecoilJetPt_%s_%s_PartLevel_tt_%d", RTypepo[ij].Data(), trg[ig].Data(), trigRangeLow);
			TH1D* NormHist = (TH1D*) Pois_hist_RJ[ig]->Clone();
			NormHist->SetName(name);
			NormHist->Scale(1/integral);
			name = Form("; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Normalized per TT yield");
			NormHist->SetTitle(name);
			NormHist->Write();


		}
	}

	name = Form("Norm_fhRecoilJetPt_pO_MB_PartLevel_tt_%d", trigRangeLow);
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

	TLegend *leg_norm;
	leg_norm = new TLegend(0.4,0.6,0.95,0.95," ","brNDC");
	leg_norm->SetFillStyle(0); leg_norm->SetBorderSize(0); leg_norm->SetTextSize(0.03);
	leg_norm->AddEntry((TObject*) histo_OO, "pO","l");
	leg_norm->AddEntry((TObject*) histo_pp, "pp","l");
	leg_norm->Draw();

	//SavePNGandEPS(c, 0); //save as image

	outFile->Close();
}


void MakeDeltaRecoilpO(const Int_t& trigRangeLow_1, const Int_t& trigRangeLow_2){
	gROOT->Reset();
	map<Int_t, Int_t> trigRanges = {{6, 7}, {12, 20}};

/*	vector<TH1D*> hist_vector = {};

	name = Form("14_pO_Res_pois_tt_6.root");
	MakeVectorHist(hist_vector, name, trigRangeLow_1);

	name = Form("14_pO_Res_pois_tt_12.root");
	MakeVectorHist(hist_vector, name, trigRangeLow_2);

	name = Form("DeltaRecoil_tt_6-7_tt_12-20.root");
	TFile *outFile = new TFile(name, "RECREATE");
	outFile->Close();


	name = Form("14_pO_Res_pois_tt_6.root");
	TFile *nfile = TFile::Open(name, "READ");
	name = Form("Norm_fhRecoilJetPt_pO_MB_PartLevel_tt_%d", trigRangeLow_1);
	TH1D* ScRJ_1 = (TH1D*) nfile->Get(name);
	name = Form("14_pO_Res_pois_tt_12.root");
	TFile *nfile1 = TFile::Open(name, "READ");
	name = Form("Norm_fhRecoilJetPt_pp_MB_PartLevel_tt_%d", trigRangeLow_1);
	TH1D* ScRJ_2 = (TH1D*) nfile1->Get(name);


	name = Form("Delta_RecoilJetPt_pO_MB_PartLevel_tt_6-12_tt_12-20");

	TH1D* DeltaRecoil = (TH1D*) ScRJ_1->Clone();
	DeltaRecoil->Add(ScRJ_1, ScRJ_2, -1, 1);
	DeltaRecoil->SetName(name);
	name = Form(";p_{T}, GeV/c; Normalized per TT yield");
	DeltaRecoil->SetTitle(name);


	name = Form("../DeltaRecoil_tt_6-7_tt_12-20.root");
	outFile = TFile::Open(name, "UPDATE");
	DeltaRecoil->Write();
	outFile->Close();
	nfile1->Close();
	nfile->Close();

	TH1D* ScRJ_1_graph = (TH1D*) ScRJ_1g->Clone();
	TH1D* ScRJ_2_graph = (TH1D*) ScRJ_2g->Clone();

	ScRJ_1_graph->SetDirectory(0);
	ScRJ_1_graph->SetLineColor(1);
	ScRJ_1_graph->SetMarkerColor(1);

	ScRJ_2_graph->SetDirectory(0);
	ScRJ_2_graph->SetLineColor(2);
	ScRJ_2_graph->SetMarkerColor(2);
*/

	name = Form("14_pO_Res_pois_tt_6.root");
	TFile* f1 = TFile::Open(name, "READ");
	name = Form("14_pO_Res_pois_tt_12.root");
	TFile* f2 = TFile::Open(name, "READ");
	name = Form("DeltaRecoil_tt_6-7_tt_12-20.root");
	TFile *outFile = new TFile(name, "RECREATE");
	outFile->Close();

	for(Int_t ig = kMB; ig< kTRIG; ig++){
		for(Int_t ij = kOO; ij< ktr; ij++){
			name = Form("Norm_fhRecoilJetPt_%s_%s_PartLevel_tt_%d", RTypepo[ij].Data(), trg[ig].Data(), trigRangeLow_1);
			TH1D* ScRJ_1 = (TH1D*) f1->Get(name);
			name = Form("Norm_fhRecoilJetPt_%s_%s_PartLevel_tt_%d", RTypepo[ij].Data(), trg[ig].Data(), trigRangeLow_2);
			TH1D* ScRJ_2 = (TH1D*) f2->Get(name);

			name = Form("Delta_RecoilJetPt_%s_%s_PartLevel_tt_%d-%d_tt_%d-%d", RTypepo[ij].Data(),
						trg[ig].Data(),
						trigRangeLow_1,
						trigRanges.at(trigRangeLow_1),
						trigRangeLow_2,
						trigRanges.at(trigRangeLow_2));

			TH1D* DeltaRecoil = (TH1D*) ScRJ_1->Clone();
			DeltaRecoil->Add(ScRJ_1, ScRJ_2, -1, 1);
			DeltaRecoil->SetName(name);
			name = Form("%s #Delta_{recoil} histogram for %s at TT p_{T} ranges %d-%d && %d-%d GeV/c; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Normalized per TT yield", trg[ig].Data(),
						RType[ij].Data(),
						trigRangeLow_1,
						trigRanges.at(trigRangeLow_1),
						trigRangeLow_2,
						trigRanges.at(trigRangeLow_2));
			DeltaRecoil->SetTitle(name);


			name = Form("DeltaRecoil_tt_%d-%d_tt_%d-%d.root", trigRangeLow_1, trigRanges.at(trigRangeLow_1), trigRangeLow_2, trigRanges.at(trigRangeLow_2));
			outFile = TFile::Open(name, "UPDATE");
			DeltaRecoil->Write();
			outFile->Close();

			delete ScRJ_1;
			delete ScRJ_2;
			delete DeltaRecoil;
		}
	}
	f1->Close();
	f2->Close();
	outFile->Close();

	TF1* func = new TF1("expoconst", appr_func, 0, 180, 3);
	func->SetParameters(1e-2, 2e1, 0.);
	func->SetParNames("Constant", "Slope", "Shift");
	func->SetParLimits(0, 1e-2, 1e-1);
	func->FixParameter(2, 0.);

	name = Form("DeltaRecoil_tt_%d-%d_tt_%d-%d.root", trigRangeLow_1, trigRanges.at(trigRangeLow_1), trigRangeLow_2, trigRanges.at(trigRangeLow_2));
	outFile = TFile::Open(name, "UPDATE");

	name = Form("Delta_RecoilJetPt_%s_%s_PartLevel_tt_%d-%d_tt_%d-%d", RType[1].Data(),
					trg[0].Data(),
					trigRangeLow_1,
					trigRanges.at(trigRangeLow_1),
					trigRangeLow_2,
					trigRanges.at(trigRangeLow_2));
	TH1D* DRJ_pp = (TH1D*) outFile->Get(name);
	//DRJ_pp->SetTitle(name);
	DRJ_pp->SetMarkerColor(1);
	DRJ_pp->SetLineColor(1);

	cout << "For pp: " << endl;
	DRJ_pp->Fit("expoconst","R","",20.,50.);

	TF1 *fit_pp = DRJ_pp->GetFunction("expoconst");
	Double_t chi2_fit_pp = fit_pp->GetChisquare();
	Double_t const_fit = fit_pp->GetParameter(0);
	Double_t slope = fit_pp->GetParameter(1);
	cout << "Chi2: " << chi2_fit_pp << endl;

	name = Form("Delta_RecoilJetPt_%s_%s_PartLevel_tt_%d-%d_tt_%d-%d", RTypepo[0].Data(),
						trg[0].Data(),
						trigRangeLow_1,
						trigRanges.at(trigRangeLow_1),
						trigRangeLow_2,
						trigRanges.at(trigRangeLow_2));
	TH1D* DRJ_OO = (TH1D*) outFile->Get(name);
	//DRJ_OO->SetTitle(name);
	DRJ_OO->SetMarkerColor(4);
	DRJ_OO->SetLineColor(4);
	func->FixParameter(0, const_fit);
	func->FixParameter(1, slope);
	func->ReleaseParameter(2);
	//TH1D* gs = (TH1D*) DRJ_OO->Clone();
	DRJ_OO->Fit("expoconst","R","",20.,50.);

	/*TF1* fitres = DRJ_OO->GetFunction("expoconst");
	Double_t fit_slope = fitres->GetParameter(1);
	Double_t fit_shift = fitres->GetParameter(2);
	Double_t fit_shift_err = fitres->GetParError(2);
	//Double_t calc_rat = TMath::Exp(-fit_shift/fit_slope);*/

	name = Form("canv_delta_recoils_rng_%d-%d", trigRangeLow_1, trigRangeLow_2);
	TCanvas* c1 = new TCanvas("canv_delta_recoils", name, 0., 0., 1000., 800.);
	c1->cd();
	gPad->SetLogy();
	DRJ_OO->SetDirectory(0);
	DRJ_pp->SetDirectory(0);
	DRJ_pp->SetMarkerColor(2);
	DRJ_pp->SetLineColor(2);

	DRJ_pp->GetXaxis()->SetRangeUser(20.,50.);
	DRJ_pp->SetTitle("");
	DRJ_OO->GetXaxis()->SetRangeUser(20.,50.);
	DRJ_OO->SetTitle("");

	DRJ_OO->GetXaxis()->SetTitle("#it{p}_{T,jet}^{ch}");
    DRJ_OO->GetYaxis()->SetTitle("#Delta_{recoil}");
	(*DRJ_OO).Draw();
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	//gs->Draw("same");
	gPad->Modified();
	gPad->Update();
	TF1* fr2 = (TF1*)DRJ_OO->GetListOfFunctions()->FindObject("expoconst");
	fr2->SetLineColor(4);
	fr2->Draw("same");
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	//gs->Draw("same");
	gPad->Modified();
	gPad->Update();

	(*DRJ_pp).Draw("same");
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	//gs->Draw("same");
	gPad->Modified();
	gPad->Update();
	TF1* fr1 = (TF1*)DRJ_pp->GetListOfFunctions()->FindObject("expoconst");
	fr1->SetLineColor(2);
	fr1->Draw("same");
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	//gs->Draw("same");
	gPad->Modified();
	gPad->Update();

    TLegend* leg3 = new TLegend(0.5,0.55,0.95,1.," ","brNDC");
    leg3->SetFillStyle(0);
    leg3->SetBorderSize(0);
    leg3->SetTextSize(0.05);
	leg3->AddEntry((TF1*) fr1, "pp","l");
	leg3->AddEntry((TF1*) fr2, "OO","l");
    leg3->Draw();

	SavePNGandEPS(c1, 0);

	name = Form("ratio_delta_recoil_rng_%d-%d", trigRangeLow_1, trigRangeLow_2);
	TCanvas* c2 = new TCanvas("canv_recoil_ratio", name, 0., 0., 800., 800.);
	c2->cd(0);

	TH1D* DRJ_ratio = new TH1D("DRJ_ratio", "", 200, -20, 180);
	DRJ_ratio->SetDirectory(0);
	DRJ_ratio->SetName("ratio");
	DRJ_ratio->Divide(DRJ_OO, DRJ_pp, 1, 1);
	DRJ_ratio->SetMarkerColor(4);
	DRJ_ratio->SetLineColor(4);
	DRJ_ratio->GetXaxis()->SetRangeUser(20., 50.);

	TF1* const_form = new TF1("const_form", "[0]", 0, 180);
	const_form->SetParName(0, "Ratio value");
	DRJ_ratio->Fit("const_form", "NR", "" , 20, 50);

	TF1* min_const_form = new TF1("min_const_form", "1+[0]", 0, 180);
	min_const_form->SetParName(0, "Shift of ratio from 1");
	DRJ_ratio->Fit("min_const_form", "NR", "" , 20, 50);

	TF1* const_form_exp = new TF1("const_form_1", "exp(-[0]/[1])", 0, 180);
	const_form_exp->SetParName(0, "Shift");
	const_form_exp->SetParName(1, "Slope");
	const_form_exp->FixParameter(1, slope);
	DRJ_ratio->Fit("const_form_1", "R", "" , 20, 50);
	TF1* fitres_ratio = (TF1*)DRJ_ratio->GetListOfFunctions()->FindObject("const_form_1");
	Double_t fit_ratio = fitres_ratio->GetParameter(0);
	Double_t fiterr = fitres_ratio->GetParError(0);
	cout << endl << "Calculated ratio: " << fit_ratio << " " << fiterr << endl;

	DRJ_ratio->Draw();
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	gPad->Modified();
	gPad->Update();

	TLegend *leg_ratio;
	leg_ratio = new TLegend(0.1,0.8,0.85,0.9," ","brNDC");
	leg_ratio->SetFillStyle(0); leg_ratio->SetBorderSize(0); leg_ratio->SetTextSize(0.03);
	leg_ratio->AddEntry((TObject*) 0, "TT range = 6-7 && 12-20 GeV","");

	ostringstream valueToConvert;
	string s_fit_ratio = "";
	string s_fiterr = "";
	valueToConvert.precision(1);
	valueToConvert << scientific << fit_ratio;
	s_fit_ratio = valueToConvert.str();
	valueToConvert.str("");
	valueToConvert << scientific << fiterr;
	s_fiterr = valueToConvert.str();

	name = Form("Results of fit ratio: s = %s #pm %s", s_fit_ratio.c_str(), s_fiterr.c_str());
	leg_ratio->AddEntry((TObject*) 0, name,"");

	leg_ratio->Draw();

	TLine* unity = new TLine(20., 1., 50., 1.);
	unity->SetLineStyle(2);
	unity->Draw();

	SavePNGandEPS(c2, 0);


	outFile->Close();

	delete func;
}
