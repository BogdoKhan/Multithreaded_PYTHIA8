STRUCTURE

//Common used functions

ProcFunctions.h

|---void SavePNGandEPS(TCanvas* mycanv, bool isEPS);//save TCanvas with content, 0-PNG, 1-EPS

|---void MakeDir(const string& dirpath, const string& dirname);//check if folder exists, if not, creates

|---int intRand(const int & min, const int & max, vector<mt19937*>& gens);//thread-safe random int generator


//File with main functions for data processing

MergeHist.cc

|---int GetSummarySpectrum(const Int_t& seed, const Int_t& TTLow);//sum over hard bins

|---void Scaling(Int_t trigRangeLow, Double_t luminosity_OO);//scale on lumi

|---void DoPoisSmearing(Int_t trigRangeLow);//make Poisson smearing

|---Double_t appr_func(Double_t* x, Double_t* par);//shifted decay exponent approx function

|---void CalculateAQ(Double_t sigma);//calculate alpha quantile for CL = 90%


//-----------HISTOGRAM-BUILDING FUNCTION SETS----------------

//Delta_recoil for pp and OO

|-OO_DeltaRecHisto.cc

..|---void MakeDeltaRecoilSp(const Int_t& trigRangeLow_1, const Int_t& trigRangeLow_2);

..//build Delta_recoil for OO and pp normalized spectra


//Centrality histograms

|-CentralityHisto.cc

..|---void MakeMuliplicitiesHistos();//build centrality dependent histos


//Energy shift dependent on tune based on 5.02 pp (Monash tune)

|-TunesHist.cc

..|---void TunesHistos();//build energy shift histos for pp


//Same, but for pO

|-pOHist.cc

..|---void protoxy_Histos();//build pO histos


//Drawing histograms

DrawGraphs.cc

|---void SetCanvas(TCanvas* c);//set TCanvas parameters

|---void SetHist(TH1* h,TString titx, TString tity);//set histo parameters

|---Int_t Draw();//draws histos with multiple TT
