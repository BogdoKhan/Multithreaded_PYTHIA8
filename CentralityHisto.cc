#include "MergeHist.cc"

void MakeMuliplicitiesHistos(){
	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.15);
	gStyle->SetPadRightMargin(0.05);

	name = Form("../TT-12_20/Res_scaled_tt_12.root");
	TFile *inFile = new TFile(name, "READ");

	name = Form("Res_multiplicities_tt_12.root");
	TFile *outFile = new TFile(name, "RECREATE");
	outFile->cd();

	name = Form("hTT_OO_MB_PartLevel_tt_12");
	TH1D* htt_low = (TH1D*) inFile->Get(name);
	TH1D* htt_high = (TH1D*) htt_low->Clone();

	name = Form("Peri_hTT_OO_MB_PartLevel_tt_12");
	htt_low = Scaler(htt_low, name, 0.5);
	name = Form("Peripheral low multiplicity trigger tracks histogram for OO at GeV/c; p_{T}, #frac{GeV}{#it{c}}; Counts");
	htt_low->SetTitle(name);

	htt_low->Write();
	Double_t integral_low = htt_low->Integral();

	name = Form("Central_hTT_OO_MB_PartLevel_tt_12");
	htt_high = Scaler(htt_high, name, 0.2);
	name = Form("Central high multiplicity trigger tracks histogram for pp at GeV/c; p_{T}, #frac{GeV}{#it{c}}; Counts");
	htt_high->SetTitle(name);
	htt_high->Write();
	Double_t integral_high = htt_high->Integral();


	name = Form("fhRecoilJetPt_OO_MB_PartLevel_tt_12");
	TH1D* hpt_low = (TH1D*) inFile->Get(name);
	TH1D* hpt_high = (TH1D*) hpt_low->Clone();

	name = Form("Peri_fhRecoilJetPt_OO_MB_PartLevel_tt_12");
	hpt_low = Scaler(hpt_low, name, 0.5);
	name = Form("Unsmeared peripheral Low-50p recoil jets histogram for OO at 12 GeV/c; p_{T}, #frac{GeV}{#it{c}}; Counts");
	hpt_low->SetTitle(name);
	hpt_low->Write();

	name = Form("Central_fhRecoilJetPt_pp_MB_PartLevel_tt_12");
	hpt_high = Scaler(hpt_high, name, 0.2);
	name = Form("Unsmeared central High-20p recoil jets histogram for pp at 12 GeV/c; p_{T}, #frac{GeV}{#it{c}}; Counts");
	hpt_high->SetTitle(name);
	hpt_high->Write();

	TH1D* hptpl = MakePois(outFile, "Peri_fhRecoilJetPt_OO_MB_PartLevel_tt_12");
	name = Form("Peri_fhRecoilJetPt_OO_MB_PartLevel_tt_12");
	hptpl->SetName(name);
	name = Form("Peripheral recoil jets histogram for OO at 12-20 GeV/c; p_{T}, #frac{GeV}{#it{c}}; Counts");
	hptpl->SetTitle(name);
	hptpl->Write();

	TH1D* hptph = MakePois(outFile, "Central_fhRecoilJetPt_pp_MB_PartLevel_tt_12");
	name = Form("Central_fhRecoilJetPt_pp_MB_PartLevel_tt_12");
	hptph->SetName(name);
	name = Form("Central recoil jets histogram for OO at 12-20 GeV/c; p_{T}, #frac{GeV}{#it{c}}; Counts");
	hptph->SetTitle(name);
	hptph->Write();

	TF1* func = new TF1("expoconst", appr_func, 0, 180, 3);
	func->SetParameters(1e-2, 2e1, 0.);
	func->SetParNames("Constant", "Slope", "Shift");
	func->SetParLimits(0, 1e-2, 1e-1);
	func->FixParameter(2, 0.);


	TH1D* Scaled_hptpl = (TH1D*) hptpl->Clone();
	Scaled_hptpl->SetDirectory(0);
	Scaled_hptpl->Scale(1/integral_low);
	name = Form("Scaled_low_RecoilJetPt_PartLevel_tt_12-20");
	Scaled_hptpl->SetName(name);
	name = Form("Peripheral normalized per TT recoil jets histogram at 12-20 GeV/c; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Normalized per TT yield");
	Scaled_hptpl->SetTitle(name);
	Scaled_hptpl->Write();
	Scaled_hptpl->Fit("expoconst","R0","",20.,50.);

	TF1 *fit_pl = Scaled_hptpl->GetFunction("expoconst");
	Double_t chi2_fit_pl = fit_pl->GetChisquare();
	Double_t const_fit = fit_pl->GetParameter(0);
	Double_t slope = fit_pl->GetParameter(1);
	cout << "Chi2: " << chi2_fit_pl << endl;

	TH1D* Scaled_hptph = (TH1D*) hptph->Clone();
	Scaled_hptph->SetDirectory(0);
	Scaled_hptph->Scale(1/integral_high);
	name = Form("Scaled_high_RecoilJetPt_PartLevel_tt_12-20");
	Scaled_hptph->SetName(name);
	name = Form("Central normalized per TT recoil jets histogram at 12-20 GeV/c; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Normalized per TT yield");
	Scaled_hptph->SetTitle(name);
	Scaled_hptph->Write();



	TH1D* hptratio = new TH1D("MRJ_ratio", "", 200, -20, 180);
	hptratio->SetDirectory(0);
	hptratio->SetName("Centrality_ratio");
	name = Form("Centrality ratio recoil jets histogram at 12-20 GeV/c; #it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}; Ratio, arb.units");
	hptratio->SetTitle("");
	hptratio->GetXaxis()->SetRangeUser(20.,50.);

	hptratio->Divide(Scaled_hptph, Scaled_hptpl, 1, 1);
	hptratio->SetMarkerColor(4);
	hptratio->SetLineColor(4);
	hptratio->Write();

	TF1* const_form_exp1 = new TF1("const_form_11", "exp(-[0]/[1])", 0, 180);
	const_form_exp1->SetParName(0, "Shift");
	const_form_exp1->SetParName(1, "Slope");
	const_form_exp1->FixParameter(1, slope);
	hptratio->Fit("const_form_11", "R", "" , 20, 50);
	TF1* fitres_ratio1 = (TF1*)hptratio->GetListOfFunctions()->FindObject("const_form_11");
	Double_t fit_ratio1 = fitres_ratio1->GetParameter(0);
	Double_t fiterr1 = fitres_ratio1->GetParError(0);
	//cout << endl << "Calculated ratio: " << calc_rat << endl;
	cout << endl << "Calculated ratio: " << fit_ratio1 << " " << fiterr1 << endl;

	name = Form("ratio_delta_recoil_rng_6-12");
	TCanvas* cr1 = new TCanvas("canv_centr_ratio", name, 0., 0., 1000., 800.);
	cr1->cd(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	hptratio->GetXaxis()->SetTitle("#it{p}_{T,jet}^{ch}, #frac{GeV}{#it{c}}");
    hptratio->GetYaxis()->SetTitle("#frac{#Delta_{recoil}^{central}(#it{p}_{T,jet}^{ch})}{#Delta_{recoil}^{peripheral}(#it{p}_{T,jet}^{ch})}");
	//#left[#font[122]{-} #frac{#bar{#it{s}}}{#it{b}}#right]}
	hptratio->SetTitleOffset(1.7, "xy");
	hptratio->Draw();


	TLegend *leg_ratio1;
	leg_ratio1 = new TLegend(0.1,0.8,0.85,0.9," ","brNDC");
	leg_ratio1->SetFillStyle(0); leg_ratio1->SetBorderSize(0); leg_ratio1->SetTextSize(0.03);
	leg_ratio1->AddEntry((TObject*) 0, "TT range = 12-20 GeV/c, L = 0.5 nb^{-1}","");

	ostringstream valueToConvert;
	string s_fit_ratio = "";
	string s_fiterr = "";
	valueToConvert.precision(1);
	valueToConvert << scientific << fit_ratio1;
	s_fit_ratio = valueToConvert.str();
	valueToConvert.str("");
	valueToConvert << scientific << fiterr1;
	s_fiterr = valueToConvert.str();

	name = Form("Results of fit ratio: s = %s #pm %s", s_fit_ratio.c_str(), s_fiterr.c_str());
	leg_ratio1->AddEntry((TObject*) 0, name,"");
	leg_ratio1->Draw();


	TLine* unity1 = new TLine(20., 1., 50., 1.);
	unity1->SetLineStyle(2);
	unity1->Draw();

	SavePNGandEPS(cr1, 0);

}
