#include "MergeHist.cc"

void TunesHistos(){
	name = Form("5_502_Res_scaled_tt_6.root");
	TFile *inFile0 = new TFile(name, "READ");

	name = Form("tunes.root");
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
	name = Form("5_635_Res_scaled_tt_6.root");
	TFile *inFile2 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pp_MB_PartLevel_tt_6");
	TH1D* htt_5635 = (TH1D*) inFile2->Get(name);
	name = Form("5_635_hTT_pp_MB_PartLevel_tt_6");
	htt_5635->SetTitle(name);
	integral = htt_5635->Integral();

	name = Form("fhRecoilJetPt_pp_MB_PartLevel_tt_6");
	TH1D* hpt_5635 = (TH1D*) inFile2->Get(name);
	name = Form("5_635_RJ_pp_MB_PartLevel_tt_6");
	hpt_5635->SetTitle(name);
	hpt_5635 = Scaler(hpt_5635, name, 1/integral);
	hpt_5635->Write();
	//inFile2->Close();
	//----------------------
	name = Form("5_635_Res_scaled_tt_12.root");
	TFile *inFile3 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pp_MB_PartLevel_tt_12");
	TH1D* htt_5635_1 = (TH1D*) inFile3->Get(name);
	name = Form("5_635_hTT_pp_MB_PartLevel_tt_12");
	htt_5635_1->SetTitle(name);
	integral = htt_5635_1->Integral();

	name = Form("fhRecoilJetPt_pp_MB_PartLevel_tt_12");
	TH1D* hpt_5635_1 = (TH1D*) inFile3->Get(name);
	name = Form("5_635_RJ_pp_MB_PartLevel_tt_12");
	hpt_5635_1->SetTitle(name);
	hpt_5635_1 = Scaler(hpt_5635_1, name, 1/integral);
	hpt_5635_1->Write();
	//inFile3->Close();
	//------------------------------
	TH1D* nhpt_5635 = (TH1D*) hpt_5635->Clone("5_635_NRJ_pp");
	nhpt_5635->Add(hpt_5635_1, hpt_5635, 1, -1);
	name = Form("5_635_NRJ_pp");
	nhpt_5635->SetTitle(name);
	nhpt_5635->Write();
	//------------------------------------------
	TH1D* dnhpt_5 = (TH1D*) hpt_5635->Clone("5_DNRJ_pp");
	dnhpt_5->Divide(nhpt_5635, nhpt_5502, 1, 1);
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
	name = Form("14_635_Res_scaled_tt_6.root");
	TFile *inFile6 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pp_MB_PartLevel_tt_6");
	TH1D* htt_14635 = (TH1D*) inFile6->Get(name);
	name = Form("14_635_hTT_pp_MB_PartLevel_tt_6");
	htt_14635->SetTitle(name);
	integral = htt_14635->Integral();

	name = Form("fhRecoilJetPt_pp_MB_PartLevel_tt_6");
	TH1D* hpt_14635 = (TH1D*) inFile6->Get(name);
	name = Form("14_635_RJ_pp_MB_PartLevel_tt_6");
	hpt_14635->SetTitle(name);
	hpt_14635 = Scaler(hpt_14635, name, 1/integral);
	hpt_14635->Write();
	//inFile6->Close();
	//-----------------------------------
	name = Form("14_635_Res_scaled_tt_12.root");
	TFile *inFile7 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pp_MB_PartLevel_tt_12");
	TH1D* htt_14635_1 = (TH1D*) inFile7->Get(name);
	name = Form("14_635_hTT_pp_MB_PartLevel_tt_12");
	htt_14635_1->SetTitle(name);
	integral = htt_14635_1->Integral();

	name = Form("fhRecoilJetPt_pp_MB_PartLevel_tt_12");
	TH1D* hpt_14635_1 = (TH1D*) inFile7->Get(name);
	name = Form("14_635_RJ_pp_MB_PartLevel_tt_12");
	hpt_14635_1->SetTitle(name);
	hpt_14635_1 = Scaler(hpt_14635_1, name, 1/integral);
	hpt_14635_1->Write();
	//inFile7->Close();
	//---------------------------------
	TH1D* nhpt_14635 = (TH1D*) hpt_14635->Clone("14_635_NRJ_pp");
	nhpt_14635->Add(hpt_14635_1, hpt_14635, 1, -1);
	name = Form("14_635_NRJ_pp");
	nhpt_14635->SetTitle(name);
	nhpt_14635->Write();
	//------------------------------------------
	TH1D* dnhpt_14 = (TH1D*) hpt_14635->Clone("14_DNRJ_pp");
	dnhpt_14->Divide(nhpt_14635, nhpt_14502, 1, 1);
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
	name = Form("21_635_Res_scaled_tt_6.root");
	TFile *inFile10 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pp_MB_PartLevel_tt_6");
	TH1D* htt_21635 = (TH1D*) inFile10->Get(name);
	name = Form("21_635_hTT_pp_MB_PartLevel_tt_6");
	htt_21635->SetTitle(name);
	integral = htt_21635->Integral();

	name = Form("fhRecoilJetPt_pp_MB_PartLevel_tt_6");
	TH1D* hpt_21635 = (TH1D*) inFile10->Get(name);
	name = Form("21_635_RJ_pp_MB_PartLevel_tt_6");
	hpt_21635->SetTitle(name);
	hpt_21635 = Scaler(hpt_21635, name, 1/integral);
	hpt_21635->Write();
	//inFile10->Close();
	//---------------------------
	name = Form("21_635_Res_scaled_tt_12.root");
	TFile *inFile11 = new TFile(name, "READ");
	outFile->cd();

	name = Form("hTT_pp_MB_PartLevel_tt_12");
	TH1D* htt_21635_1 = (TH1D*) inFile11->Get(name);
	name = Form("21_635_hTT_pp_MB_PartLevel_tt_12");
	htt_21635_1->SetTitle(name);
	integral = htt_21635_1->Integral();

	name = Form("fhRecoilJetPt_pp_MB_PartLevel_tt_12");
	TH1D* hpt_21635_1 = (TH1D*) inFile11->Get(name);
	name = Form("21_635_RJ_pp_MB_PartLevel_tt_12");
	hpt_21635_1->SetTitle(name);
	hpt_21635_1 = Scaler(hpt_21635_1, name, 1/integral);
	hpt_21635_1->Write();
	//inFile11->Close();
	//-----------------------------
	TH1D* nhpt_21635 = (TH1D*) hpt_21635->Clone("21_635_NRJ_pp");
	nhpt_21635->Add(hpt_21635_1, hpt_21635, 1, -1);
	name = Form("21_635_NRJ_pp");
	nhpt_21635->SetTitle(name);
	nhpt_21635->Write();
	//------------------------------------------
	TH1D* dnhpt_21 = (TH1D*) hpt_21635->Clone("21_DNRJ_pp");
	dnhpt_21->Divide(nhpt_21635, nhpt_21502, 1, 1);
	name = Form("21_DNRJ_pp");
	dnhpt_21->SetTitle(name);
	dnhpt_21->Write();
	//------------------------------------------


	//dnhpt_5 nhpt_14502
	//dnhpt_14
	//dnhpt_21
	//outFile->Close();

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
	dnhpt_5->GetYaxis()->SetRangeUser(0.9, 1.15);
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


	TCanvas* c4 = new TCanvas("MBd", "mbd", 0., 0., 1000., 800.);
	c4->cd(0);

	TH1D* shpt_5 = (TH1D*) nhpt_14502->Clone("5_ScaledTo635");
	shpt_5->SetLineColor(1);
	shpt_5->SetMarkerColor(1);
	shpt_5->Multiply(fit5_l, 1);
	shpt_5->GetXaxis()->SetRangeUser(20., 50.);
	shpt_5->Write();

	TH1D* shpt_14 = (TH1D*) nhpt_14502->Clone("14_ScaledTo635");
	shpt_14->SetLineColor(2);
	shpt_14->SetMarkerColor(2);
	shpt_14->Multiply(fit14_l, 1);
	shpt_14->GetXaxis()->SetRangeUser(20., 50.);
	shpt_14->GetYaxis()->SetMaxDigits(2);
	shpt_14->Write();

	TH1D* shpt_21 = (TH1D*) nhpt_14502->Clone("21_ScaledTo635");
	shpt_21->SetLineColor(3);
	shpt_21->SetMarkerColor(3);
	shpt_21->Multiply(fit21_l, 1);
	shpt_21->GetXaxis()->SetRangeUser(20., 50.);
	shpt_21->Write();


	cout << "======================TUNE 14 base=======================" << endl;
	nhpt_14502->Fit("expoconst","R","",20.,50.);
	//shpt_14->Fit("expoconst","R","",20.,50.);
	TF1* fit_pl = nhpt_14502->GetFunction("expoconst");
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

	shpt_14->GetXaxis()->SetTitle("#it{p}_{T,jet}^{ch}");
    shpt_14->GetYaxis()->SetTitle("#Delta_{recoil, tune_{i}}^{6.37 TeV}, (GeV/c)^{-1}");
	shpt_14->SetTitle("");
}
