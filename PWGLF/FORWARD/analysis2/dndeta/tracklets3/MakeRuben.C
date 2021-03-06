/**
 * @file   MakeRuben.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Tue Sep 20 17:13:34 2016
 * 
 * @brief  
 * 
 * 
 * @ingroup pwglf_forward_tracklets
 */
/** 
 * @{ 
 * @name Make Ruben's weights 
 *
 * @ingroup pwglf_forward_tracklets
 */
/** 
 * Make Ruben's weights
 * 
 * @relates AliTrackletBaseWeights
 */
void
MakeRuben()
{
  gSystem->AddIncludePath("-I${ALICE_ROOT}/include -I${ALICE_PHYSICS}/include");
  gROOT->LoadMacro("AliAODTracklet.C+g");
  gROOT->LoadMacro("AliTrackletWeights.C+g");

  AliTrackletPtPidStrWeights* weights = new AliTrackletPtPidStrWeights("weights");
  weights->SetMask(AliAODTracklet::kGenerated);
  weights->SetVeto(0x0);
    
  // --- pT weight ---------------------------------------------------
  // Unity in all centralities and pT 
  // TH2D* cPt = new TH2D("cPt", "cPt", 1, 0, 100, 1, 0, 5);
  // cPt->SetBinContent(1,1,1);
  // weights->SetPtWeight(cPt);

  // --- Abundance weights -------------------------------------------
  // We do not add any!

  // --- Strangeness weights -----------------------------------------
  // We add simple constant weights
  Short_t pids[] = { 321, // K^+/-
		     310, // K^0_S
		     3122, // Lambda
		     3212, // Sigma0
		     3322, // Xi0,
		     0 };
  Double_t factors[] = { 1.5,
			 1.5,
			 3,
			 3,
			 3,
			 0 };
  Short_t*  pid = pids;
  Double_t* fac = factors;
  while (*pid) {
    Short_t  p = *pid;
    Double_t f = *fac;
    TH1D*   h = new TH1D(Form("w%d", p), Form("PID %d weight", p), 1, 0, 100);
    h->SetBinContent(1,f);
    weights->AddStrangenessWeight(p, h);
    pid++;
    fac++;
  }

  new TBrowser;
  
  // --- Write to file -----------------------------------------------
  TFile* outW = TFile::Open("ruben.root", "RECREATE");  
  weights->Write();
  outW->Write();
  weights->Draw();
  weights->Print();
}
/* @} */
//
// EOF
//
