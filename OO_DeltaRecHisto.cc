#include "MergeHist.cc"

void MakeDeltaRecoilSp(const Int_t& trigRangeLow_1, const Int_t& trigRangeLow_2){
	gROOT->Reset();
	map<Int_t, Int_t> trigRanges = {{6, 7}, {12, 20}, {20, 30}};

	vector<TH1D*> hist_vector = {};

	name = Form("../TT-%d_%d/Res_pois_tt_%d.root", trigRangeLow_1, trigRanges.at(trigRangeLow_1), trigRangeLow_1);
	MakeVectorHist(hist_vector, name, trigRangeLow_1);

	name = Form("../TT-%d_%d/Res_pois_tt_%d.root", trigRangeLow_2, trigRanges.at(trigRangeLow_2), trigRangeLow_2);
	MakeVectorHist(hist_vector, name, trigRangeLow_2);

	name = Form("../DeltaRecoil_tt_%d-%d_tt_%d-%d.root", trigRangeLow_1, trigRanges.at(trigRangeLow_1), trigRangeLow_2, trigRanges.at(trigRangeLow_2));
	TFile *outFile = new TFile(name, "RECREATE");
	outFile->Close();


	name = Form("../TT-%d_%d/Normalized_by_tt_%d.root", trigRangeLow_1, trigRanges.at(trigRangeLow_1), trigRangeLow_1);
	TFile *nfile = TFile::Open(name, "READ");
	name = Form("Scaled_RecoilJetPt_OO_MB_PartLevel_tt_%d", trigRangeLow_1);
	TH1D* ScRJ_1g = (TH1D*) nfile->Get(name);
	name = Form("Scaled_RecoilJetPt_pp_MB_PartLevel_tt_%d", trigRangeLow_1);
	TH1D* ScRJ_2g = (TH1D*) nfile->Get(name);
	TH1D* ScRJ_1_graph = (TH1D*) ScRJ_1g->Clone();
	TH1D* ScRJ_2_graph = (TH1D*) ScRJ_2g->Clone();

	ScRJ_1_graph->SetDirectory(0);
	ScRJ_1_graph->SetLineColor(1);
	ScRJ_1_graph->SetMarkerColor(1);

	ScRJ_2_graph->SetDirectory(0);
	ScRJ_2_graph->SetLineColor(2);
	ScRJ_2_graph->SetMarkerColor(2);


	name = Form("../TT-%d_%d/Normalized_by_tt_%d.root", trigRangeLow_1, trigRanges.at(trigRangeLow_1), trigRangeLow_1);
	TFile* f1 = TFile::Open(name, "READ");
	cout << "b";
	name = Form("../TT-%d_%d/Normalized_by_tt_%d.root", trigRangeLow_2, trigRanges.at(trigRangeLow_2), trigRangeLow_2);
	TFile* f2 = TFile::Open(name, "READ");
	cout << "bb";


	for(Int_t ig = kMB; ig< kTRIG; ig++){
		for(Int_t ij = kOO; ij< ktr; ij++){
			name = Form("Scaled_RecoilJetPt_%s_%s_PartLevel_tt_%d", RType[ij].Data(), trg[ig].Data(), trigRangeLow_1);
			TH1D* ScRJ_1 = (TH1D*) f1->Get(name);
			name = Form("Scaled_RecoilJetPt_%s_%s_PartLevel_tt_%d", RType[ij].Data(), trg[ig].Data(), trigRangeLow_2);
			TH1D* ScRJ_2 = (TH1D*) f2->Get(name);

			name = Form("Delta_RecoilJetPt_%s_%s_PartLevel_tt_%d-%d_tt_%d-%d", RType[ij].Data(),
						trg[ig].Data(),
						trigRangeLow_1,
						trigRanges.at(trigRangeLow_1),
						trigRangeLow_2,
						trigRanges.at(trigRangeLow_2));

			TH1D* DeltaRecoil = (TH1D*) ScRJ_1->Clone();
			DeltaRecoil->Add(ScRJ_1, ScRJ_2, -1, 1);
			DeltaRecoil->SetName(name);
			name = Form("%s #Delta_{recoil} histogram for %s at TT p_{T} ranges %d-%d && %d-%d GeV/c; p_{T}, GeV/c; Normalized per TT yield", trg[ig].Data(),
						RType[ij].Data(),
						trigRangeLow_1,
						trigRanges.at(trigRangeLow_1),
						trigRangeLow_2,
						trigRanges.at(trigRangeLow_2));
			DeltaRecoil->SetTitle(name);


			name = Form("../DeltaRecoil_tt_%d-%d_tt_%d-%d.root", trigRangeLow_1, trigRanges.at(trigRangeLow_1), trigRangeLow_2, trigRanges.at(trigRangeLow_2));
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

	name = Form("../DeltaRecoil_tt_%d-%d_tt_%d-%d.root", trigRangeLow_1, trigRanges.at(trigRangeLow_1), trigRangeLow_2, trigRanges.at(trigRangeLow_2));
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

	name = Form("Delta_RecoilJetPt_%s_%s_PartLevel_tt_%d-%d_tt_%d-%d", RType[0].Data(),
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
