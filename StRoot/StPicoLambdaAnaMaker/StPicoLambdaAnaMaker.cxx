#include "StPicoLambdaAnaMaker.h"
//#include "StPicoHFMaker/StHFCuts.h"
#include <iostream>
#include <cmath>

ClassImp(StPicoLambdaAnaMaker)

using namespace std;

// _________________________________________________________
StPicoLambdaAnaMaker::StPicoLambdaAnaMaker(char const* name, StPicoDstMaker* picoMaker, char const* outputBaseFileName,
               char const* inputHFListHFtree = "") :
  StPicoHFMaker(name, picoMaker, outputBaseFileName, inputHFListHFtree),
  mDecayChannel(kChannel1), mOutFileBaseName(outputBaseFileName){


  // constructor
}

// _________________________________________________________
StPicoLambdaAnaMaker::~StPicoLambdaAnaMaker() {
  // destructor
}

// _________________________________________________________
int StPicoLambdaAnaMaker::InitHF() {
  // -- INITIALIZE USER HISTOGRAMS ETC HERE -------------------
  //    add them to the output list mOutList which is automatically written

  // EXAMPLE //  mOutList->Add(new TH1F(...));
  // EXAMPLE //  TH1F* hist = static_cast<TH1F*>(mOutList->Last());

  //QA histograms and TOF matching histograms
  //mOutList->Add(new TH1F("h_time_per_event","h_time_per_event", 2000., 0., 20.));

  if(isMakerMode() == StPicoHFMaker::kAnalyze)
  {

    mOutFileBaseName = mOutFileBaseName.ReplaceAll(".root", "");


    //create TTree to store Lambda candidates
    ntp_Lambda = new TTree("ntp_Lambda", "Lambda TTree"); //create TTree


    //---Set TTree branches------------------------------------------------------------------------------

    //event
    ntp_Lambda->Branch("runId", &runId, "runId/I");            //Int_t runId
    ntp_Lambda->Branch("eventId", &eventId, "eventId/I");       //Int_t eventId
    ntp_Lambda->Branch("VzVzVPDmax", &VzVzVPDmax, "VzVzVPDmax/F"); //VzVzVPDmax
    
    //leading and subleading particles
    ntp_Lambda->Branch("lead_pt", &lead_pt, "lead_pt/F");               //Float_t p1_pt
    ntp_Lambda->Branch("lead_phi", &lead_phi, "lead_phi/F");             //Float_t p1_phi
    ntp_Lambda->Branch("lead_eta", &lead_eta, "lead_eta/F");             //Float_t p1_eta
    
    ntp_Lambda->Branch("sublead_pt", &sublead_pt, "sublead_pt/F");               //Float_t p1_pt
    ntp_Lambda->Branch("sublead_phi", &sublead_phi, "sublead_phi/F");             //Float_t p1_phi
    ntp_Lambda->Branch("sublead_eta", &sublead_eta, "sublead_eta/F");             //Float_t p1_eta

    //proton
    ntp_Lambda->Branch("p1_pt", &p1_pt, "p1_pt/F");               //Float_t p1_pt
    ntp_Lambda->Branch("p1_phi", &p1_phi, "p1_phi/F");             //Float_t p1_phi
    ntp_Lambda->Branch("p1_eta", &p1_eta, "p1_eta/F");             //Float_t p1_eta
    ntp_Lambda->Branch("p1_dca", &p1_dca, "p1_dca/F");               //Float_t p1_dca
    ntp_Lambda->Branch("p1_ch", &p1_ch, "p1_ch/I");               //Float_t p1_ch
    ntp_Lambda->Branch("p1_hasTOFinfo", &p1_hasTOFinfo, "p1_hasTOFinfo/I");   //Float_t p1_hasTOFinfo

    //pion
    ntp_Lambda->Branch("p2_pt", &p2_pt, "p2_pt/F");               //Float_t p2_pt
    ntp_Lambda->Branch("p2_phi", &p2_phi, "p2_phi/F");             //Float_t p2_phi
    ntp_Lambda->Branch("p2_eta", &p2_eta, "p2_eta/F");             //Float_t p2_eta
    ntp_Lambda->Branch("p2_dca", &p2_dca, "p2_dca/F");               //Float_t p2_dca
    ntp_Lambda->Branch("p2_ch", &p2_ch, "p2_ch/F");               //Float_t p2_ch
    ntp_Lambda->Branch("p2_hasTOFinfo", &p2_hasTOFinfo, "p2_hasTOFinfo/I");   //Float_t p2_hasTOFinfo

    //pair
    ntp_Lambda->Branch("pair_charge", &pair_charge, "pair_charge/I");      //Int_t charge
    ntp_Lambda->Branch("pair_DCAdaughters", &pair_DCAdaughters, "pair_DCAdaughters/F");      //Int_t pair_DCAdaughters
    ntp_Lambda->Branch("pair_theta", &pair_theta, "pair_theta/F");   //Float_t pair_theta
    ntp_Lambda->Branch("pair_cosThetaStar", &pair_cosThetaStar, "pair_cosThetaStar/F");   //Float_t pair_cosThetaStar
    ntp_Lambda->Branch("pair_decayL", &pair_decayL, "pair_decayL/F");  //Float_t pair_decayL
    ntp_Lambda->Branch("pair_phi", &pair_phi, "pair_phi/F");      //Float_t pair_phi
    ntp_Lambda->Branch("pair_eta", &pair_eta, "pair_eta/F");      //Float_t pair_eta
    ntp_Lambda->Branch("pair_pt", &pair_pt, "pair_pt/F");        //Float_t pair_pt
    ntp_Lambda->Branch("pair_mass", &pair_mass, "pair_mass/F");    //Float_t pair_mass

    //ntp_Lambda->Branch("thetaProdPlane", &thetaProdPlane, "thetaProdPlane/F");      //Int_t thetaProdPlane
    //ntp_Lambda->Branch("prodPlane_x", &prodPlane_x, "prodPlane_x/F");      //Int_t prodPlane_x
    //ntp_Lambda->Branch("prodPlane_y", &prodPlane_y, "prodPlane_y/F");      //Int_t prodPlane_y
    //ntp_Lambda->Branch("prodPlane_z", &prodPlane_z, "prodPlane_z/F");      //Int_t prodPlane_z

    //-----------------------Set branches END------------------------------------------------------------------------------


    //create TTree to store K0s candidates
    ntp_K0s = new TTree("ntp_K0s", "K0s TTree"); //create TTree


    //---Set TTree branches------------------------------------------------------------------------------

    //event
    ntp_K0s->Branch("runId", &runId, "runId/I");            //Int_t runId
    ntp_K0s->Branch("eventId", &eventId, "eventId/I");       //Int_t eventId
    ntp_K0s->Branch("VzVzVPDmax", &VzVzVPDmax, "VzVzVPDmax/F"); //VzVzVPDmax
    
    //leading and subleading particles
    ntp_K0s->Branch("lead_pt", &lead_pt, "lead_pt/F");               //Float_t p1_pt
    ntp_K0s->Branch("lead_phi", &lead_phi, "lead_phi/F");             //Float_t p1_phi
    ntp_K0s->Branch("lead_eta", &lead_eta, "lead_eta/F");             //Float_t p1_eta
    
    ntp_K0s->Branch("sublead_pt", &sublead_pt, "sublead_pt/F");               //Float_t p1_pt
    ntp_K0s->Branch("sublead_phi", &sublead_phi, "sublead_phi/F");             //Float_t p1_phi
    ntp_K0s->Branch("sublead_eta", &sublead_eta, "sublead_eta/F");             //Float_t p1_eta

    //Pion 1
    ntp_K0s->Branch("p1_pt", &p1_pt, "p1_pt/F");               //Float_t p1_pt
    ntp_K0s->Branch("p1_phi", &p1_phi, "p1_phi/F");             //Float_t p1_phi
    ntp_K0s->Branch("p1_eta", &p1_eta, "p1_eta/F");             //Float_t p1_eta
    ntp_K0s->Branch("p1_dca", &p1_dca, "p1_dca/F");               //Float_t p1_dca
    ntp_K0s->Branch("p1_ch", &p1_ch, "p1_ch/I");               //Int_t p1_ch
    ntp_K0s->Branch("p1_hasTOFinfo", &p1_hasTOFinfo, "p1_hasTOFinfo/I");   //Float_t p1_hasTOFinfo

    //pion 2
    ntp_K0s->Branch("p2_pt", &p2_pt, "p2_pt/F");               //Float_t p2_pt
    ntp_K0s->Branch("p2_phi", &p2_phi, "p2_phi/F");             //Float_t p2_phi
    ntp_K0s->Branch("p2_eta", &p2_eta, "p2_eta/F");             //Float_t p2_eta
    ntp_K0s->Branch("p2_dca", &p2_dca, "p2_dca/F");               //Float_t p2_dca
    ntp_K0s->Branch("p2_ch", &p2_ch, "p2_ch/F");               //Float_t p2_ch
    ntp_K0s->Branch("p2_hasTOFinfo", &p2_hasTOFinfo, "p2_hasTOFinfo/I");   //Float_t p2_hasTOFinfo

    //pair
    ntp_K0s->Branch("pair_charge", &pair_charge, "pair_charge/I");      //Int_t charge
    ntp_K0s->Branch("pair_DCAdaughters", &pair_DCAdaughters, "pair_DCAdaughters/F");      //Int_t pair_DCAdaughters
    ntp_K0s->Branch("pair_theta", &pair_theta, "pair_theta/F");   //Float_t pair_theta
    ntp_K0s->Branch("pair_cosThetaStar", &pair_cosThetaStar, "pair_cosThetaStar/F");   //Float_t pair_cosThetaStar
    ntp_K0s->Branch("pair_decayL", &pair_decayL, "pair_decayL/F");  //Float_t pair_decayL
    ntp_K0s->Branch("pair_phi", &pair_phi, "pair_phi/F");      //Float_t pair_phi
    ntp_K0s->Branch("pair_eta", &pair_eta, "pair_eta/F");      //Float_t pair_eta
    ntp_K0s->Branch("pair_pt", &pair_pt, "pair_pt/F");        //Float_t pair_pt
    ntp_K0s->Branch("pair_mass", &pair_mass, "pair_mass/F");    //Float_t pair_mass

    //ntp_K0s->Branch("thetaProdPlane", &thetaProdPlane, "thetaProdPlane/F");      //Int_t thetaProdPlane
    //ntp_K0s->Branch("prodPlane_x", &prodPlane_x, "prodPlane_x/F");      //Int_t prodPlane_x
    //ntp_K0s->Branch("prodPlane_y", &prodPlane_y, "prodPlane_y/F");      //Int_t prodPlane_y
    //ntp_K0s->Branch("prodPlane_z", &prodPlane_z, "prodPlane_z/F");      //Int_t prodPlane_z

    //-----------------------Set branches END------------------------------------------------------------------------------
  }

  if(isMakerMode() == StPicoHFMaker::kQA)
  {    
      
    mOutList->Add(new TH1F("h_piTPC","h_piTPC",100,0,10));
    mOutList->Add(new TH1F("h_kTPC","h_kTPC",100,0,10));
    mOutList->Add(new TH1F("h_pTPC","h_pTPC",100,0,10));

    mOutList->Add(new TH1F("h_piTPC_prim","h_piTPC_prim",100,0,10));
    mOutList->Add(new TH1F("h_kTPC_prim","h_kTPC_prim",100,0,10));
    mOutList->Add(new TH1F("h_pTPC_prim","h_pTPC_prim",100,0,10));

    mOutList->Add(new TH2F("h_piTOF","h_piTOF",100,0,10, 2, 0, 2));
    mOutList->Add(new TH2F("h_kTOF","h_kTOF",100,0,10, 2, 0, 2));
    mOutList->Add(new TH2F("h_pTOF","h_pTOF",100,0,10, 2, 0, 2));

    mOutList->Add(new TH2F("h_piTOF_20","h_piTOF_20",100,0,10, 2, 0, 2));
    mOutList->Add(new TH2F("h_kTOF_20","h_kTOF_20",100,0,10, 2, 0, 2));
    mOutList->Add(new TH2F("h_pTOF_20","h_pTOF_20",100,0,10, 2, 0, 2));
    
    mOutList->Add(new TH2F("h_piTOF_BEMC_match","h_piTOF_BEMC_match",100,0,10, 2, 0, 2));
    mOutList->Add(new TH2F("h_kTOF_BEMC_match","h_kTOF_BEMC_match",100,0,10, 2, 0, 2));
    mOutList->Add(new TH2F("h_pTOF_BEMC_match","h_pTOF_BEMC_match",100,0,10, 2, 0, 2));

    mOutList->Add(new TH2F("h_piTOF_1sig","h_piTOF_1sig",100,0,10, 2, 0, 2));
    mOutList->Add(new TH2F("h_kTOF_1sig","h_kTOF_1sig",100,0,10, 2, 0, 2));
    mOutList->Add(new TH2F("h_pTOF_1sig","h_pTOF_1sig",100,0,10, 2, 0, 2));

    mOutList->Add(new TH2F("h_piTOFbeta","h_piTOFbeta",500,0,10, 500, 0, 5));
    mOutList->Add(new TH2F("h_kTOFbeta","h_kTOFbeta",500,0,10, 500, 0, 5));
    mOutList->Add(new TH2F("h_pTOFbeta","h_pTOFbeta",500,0,10, 500, 0, 5));

  }


  mRunNumber = 0;
  return kStOK;
}

// _________________________________________________________
void StPicoLambdaAnaMaker::ClearHF(Option_t *opt="") {
  return;
}

// _________________________________________________________
int StPicoLambdaAnaMaker::FinishHF() 
{
   if( isMakerMode() == StPicoHFMaker::kAnalyze )
   {
    ntp_Lambda->Write(); //for candidates
    ntp_K0s->Write();
   }

  return kStOK;
}

// _________________________________________________________
int StPicoLambdaAnaMaker::MakeHF() {

  //create and analyze D+- candidates

  //createCandidates() makes triplets of K and pi and checks that they pass cuts
  //analyzeCandidates() saves relevant information about the triplets to TTree

  //std::clock_t start1 = std::clock();//kvapil

  if (isMakerMode() == StPicoHFMaker::kWrite) {
    createCandidates();
  }
  else if (isMakerMode() == StPicoHFMaker::kRead) {
    // -- the reading back of the perviously written trees happens in the background
    analyzeCandidates();
  }
  else if (isMakerMode() == StPicoHFMaker::kAnalyze)
  {
    createCandidates();
    analyzeCandidates();
  

/*
    
*/ //end comment TOF histograms

  }// end if (isMakerMode() == StPicoHFMaker::kAnalyze)
  
  else if (isMakerMode() == StPicoHFMaker::kQA)
  {
    createQA();
  }


/*
    double duration = (double) (std::clock() - start1) / (double) CLOCKS_PER_SEC;
  TH1F *h_time_per_event = static_cast<TH1F*>(mOutList->FindObject("h_time_per_event"));
  h_time_per_event->Fill(duration);
*/
  return kStOK;
}


int StPicoLambdaAnaMaker::createQA()
{
 
  //QA and TOF matching histograms
  TH1F *h_piTPC = static_cast<TH1F*>(mOutList->FindObject("h_piTPC"));
  TH1F *h_kTPC = static_cast<TH1F*>(mOutList->FindObject("h_kTPC"));
  TH1F *h_pTPC = static_cast<TH1F*>(mOutList->FindObject("h_pTPC"));

  TH1F *h_piTPC_prim = static_cast<TH1F*>(mOutList->FindObject("h_piTPC_prim"));
  TH1F *h_kTPC_prim = static_cast<TH1F*>(mOutList->FindObject("h_kTPC_prim"));
  TH1F *h_pTPC_prim = static_cast<TH1F*>(mOutList->FindObject("h_pTPC_prim"));

  TH2F *h_piTOF = static_cast<TH2F*>(mOutList->FindObject("h_piTOF"));
  TH2F *h_kTOF = static_cast<TH2F*>(mOutList->FindObject("h_kTOF"));
  TH2F *h_pTOF = static_cast<TH2F*>(mOutList->FindObject("h_pTOF"));

  TH2F *h_piTOF_20 = static_cast<TH2F*>(mOutList->FindObject("h_piTOF_20"));
  TH2F *h_kTOF_20 = static_cast<TH2F*>(mOutList->FindObject("h_kTOF_20"));
  TH2F *h_pTOF_20 = static_cast<TH2F*>(mOutList->FindObject("h_pTOF_20"));
  
  TH2F *h_piTOF_BEMC_match = static_cast<TH2F*>(mOutList->FindObject("h_piTOF_BEMC_match"));
  TH2F *h_kTOF_BEMC_match = static_cast<TH2F*>(mOutList->FindObject("h_kTOF_BEMC_match"));
  TH2F *h_pTOF_BEMC_match = static_cast<TH2F*>(mOutList->FindObject("h_pTOF_BEMC_match"));

  TH2F *h_piTOF_1sig = static_cast<TH2F*>(mOutList->FindObject("h_piTOF_1sig"));
  TH2F *h_kTOF_1sig = static_cast<TH2F*>(mOutList->FindObject("h_kTOF_1sig"));
  TH2F *h_pTOF_1sig = static_cast<TH2F*>(mOutList->FindObject("h_pTOF_1sig"));

  TH2F *h_piTOFbeta = static_cast<TH2F*>(mOutList->FindObject("h_piTOFbeta"));
  TH2F *h_kTOFbeta = static_cast<TH2F*>(mOutList->FindObject("h_kTOFbeta"));
  TH2F *h_pTOFbeta = static_cast<TH2F*>(mOutList->FindObject("h_pTOFbeta"));




  //primary vertex
  TVector3 pVtx = mPicoDst->event()->primaryVertex();

 

  for (unsigned short idxPion = 0; idxPion < mIdxPicoPions.size(); ++idxPion)
  {
    StPicoTrack const *pion = mPicoDst->track(mIdxPicoPions[idxPion]);
   
   
    
    //calculate beta of track from its momentum
    float piBeta = mHFCuts->getTofBetaBase(pion, mPicoDst->event()->bField()); //SL16j, Vanek

    //get beta of track from TOF, if TOF information is available          
    Int_t piTofAvailable = 0;
    if(!isnan(piBeta) && piBeta > 0)
    {
       piTofAvailable = 1;
       float tofPion = fabs(1. / piBeta - sqrt(1+M_PION_PLUS*M_PION_PLUS/(pion->gMom().Mag()*pion->gMom().Mag())));
       h_piTOFbeta->Fill(pion->gPt(),tofPion);
    }

    //fill QA and TOF matching histograms
    h_piTOF->Fill(pion->gPt(),piTofAvailable);
    
    if (mHFCuts->hasGoodNHitsFitMinHist(pion))
    {
      h_piTPC->Fill(pion->gPt());

      if(pion->isPrimary())
      {
        h_piTPC_prim->Fill(pion->pPt());
      }

      h_piTOF_20->Fill(pion->gPt(),piTofAvailable);
      
      if(pion->isBemcTrack())
      {
        h_piTOF_BEMC_match->Fill(pion->gPt(), piTofAvailable);     
      
      }

    }

    if (mHFCuts->hasGoodNSigmaHist(pion, 1)) h_piTOF_1sig->Fill(pion->gPt(),piTofAvailable); //hasGoodNSigmaHist(pion, 1) => check nSigma of pion
      

  }
  
  
  for (unsigned short idxKaon = 0; idxKaon < mIdxPicoKaons.size(); ++idxKaon)
  {
    StPicoTrack const *kaon = mPicoDst->track(mIdxPicoKaons[idxKaon]);
   
   
    
    float kBeta = mHFCuts->getTofBetaBase(kaon, mPicoDst->event()->bField()); //SL16j, Vanek
    Int_t kTofAvailable = 0;
    if(!isnan(kBeta) && kBeta > 0)
    {
      kTofAvailable = 1;
      float tofKaon = fabs(1. / kBeta - sqrt(1+M_KAON_PLUS*M_KAON_PLUS/(kaon->gMom().Mag()*kaon->gMom().Mag())));
      h_pTOFbeta->Fill(kaon->gPt(),tofKaon);
    }

    h_pTOF->Fill(kaon->gPt(),kTofAvailable);

    if (mHFCuts->hasGoodNHitsFitMinHist(kaon))
    {
      h_pTPC->Fill(kaon->gPt());

      if(kaon->isPrimary())
      {
        h_pTPC_prim->Fill(kaon->pPt());
      }
    
      h_pTOF_20->Fill(kaon->gPt(),kTofAvailable);
      
      if(kaon->isBemcTrack())
      {
        h_kTOF_BEMC_match->Fill(kaon->gPt(), kTofAvailable);      
      }
      
    }
        
    if (fabs(mHFCuts->hasGoodNSigmaHist(kaon, 3))) h_pTOF_1sig->Fill(kaon->gPt(),kTofAvailable); //hasGoodNSigmaHist(kaon, 3) => check nSigma of kaon
       

  }
  


  for (unsigned short idxProton = 0; idxProton < mIdxPicoProtons.size(); ++idxProton)
  {
    StPicoTrack const *proton = mPicoDst->track(mIdxPicoProtons[idxProton]);
   
   
    
    float pBeta = mHFCuts->getTofBetaBase(proton, mPicoDst->event()->bField()); //SL16j, Vanek
    Int_t pTofAvailable = 0;
    if(!isnan(pBeta) && pBeta > 0)
    {
      pTofAvailable = 1;
      float tofProton = fabs(1. / pBeta - sqrt(1+M_PROTON*M_PROTON/(proton->gMom().Mag()*proton->gMom().Mag())));
      h_pTOFbeta->Fill(proton->gPt(),tofProton);
    }

    h_pTOF->Fill(proton->gPt(),pTofAvailable);

    if (mHFCuts->hasGoodNHitsFitMinHist(proton))
    {
      h_pTPC->Fill(proton->gPt());

      if(proton->isPrimary())
      {
        h_pTPC_prim->Fill(proton->pPt());
      }
    
      h_pTOF_20->Fill(proton->gPt(),pTofAvailable);
      
      if(proton->isBemcTrack())
      {
        h_pTOF_BEMC_match->Fill(proton->gPt(), pTofAvailable);      
      }
      
    }
        
    if (fabs(mHFCuts->hasGoodNSigmaHist(proton, 3))) h_pTOF_1sig->Fill(proton->gPt(),pTofAvailable); //hasGoodNSigmaHist(proton, 3) => check nSigma of proton
       

  }


       
  return 0;
}

// _________________________________________________________
int StPicoLambdaAnaMaker::createCandidates() {
  // Creating candidates for Lambda decay
  // Lambda -> p pi- decay
  
  //cout<<"start createCandidates"<<endl;

  for (unsigned short idxPion = 0; idxPion < mIdxPicoPions.size(); ++idxPion)
  {
    StPicoTrack const *pion = mPicoDst->track(mIdxPicoPions[idxPion]);
    // -- Pion selection
    
    //check that pion has TOF info here to speed up the code
    float piBetaBase = -1;

    piBetaBase = mHFCuts->getTofBetaBase(pion, mPicoDst->event()->bField());

    //get beta of track from TOF, if TOF information is available          
    int pi_hasTOFinfo = 0;

    if(!isnan(piBetaBase) && piBetaBase > 0)
    {
      pi_hasTOFinfo = 1;
    }

    if( mHFCuts->requireStrictTOF() && pi_hasTOFinfo == 0 ) continue; //strict TOF matching for pions, turned on/off in run macro
    
    

    for (unsigned short idxProton = 0; idxProton < mIdxPicoProtons.size(); ++idxProton)
    {
      StPicoTrack const *proton = mPicoDst->track(mIdxPicoProtons[idxProton]);

      if (mIdxPicoProtons[idxProton] == mIdxPicoPions[idxPion]) continue;

      // -- Making pair, want proton first for cosThetaStar calculation
      StHFPair pair(proton, pion, mHFCuts->getHypotheticalMass(StHFCuts::kProton), mHFCuts->getHypotheticalMass(StHFCuts::kPion), mIdxPicoProtons[idxProton], mIdxPicoPions[idxPion], mPrimVtx, mBField);

      //cout<<pair.prodPlane().x()<<endl;

      if(!mHFCuts->isGoodSecondaryVertexPair(pair)) continue;

      mPicoHFEvent->addHFSecondaryVertexPair(&pair);
        
    } //end for (unsigned short idxProton = 0; idxProton < mIdxPicoProtons.size(); ++idxProton)

    //create K0s candidates
    for (unsigned short idxPion2 = idxPion+1; idxPion2 < mIdxPicoPions.size(); ++idxPion2)
    {
      StPicoTrack const *pion2 = mPicoDst->track(mIdxPicoPions[idxPion2]);

      if (mIdxPicoPions[idxPion2] == mIdxPicoPions[idxPion]) continue;

      StHFPair pair2(pion, pion2, mHFCuts->getHypotheticalMass(StHFCuts::kPion), mHFCuts->getHypotheticalMass(StHFCuts::kPion), mIdxPicoPions[idxPion], mIdxPicoPions[idxPion2], mPrimVtx, mBField);

      if(!mHFCuts->isGoodSecondaryVertexPair_2(pair2)) continue;

      mPicoHFEvent->addHFSecondaryVertexPair(&pair2);

    }

//end for (unsigned short idxPion2 = idxPion+1; idxPion2 < mIdxPicoPions.size(); ++idxPion2)
  } //end for (unsigned short idxPion = 0; idxPion < mIdxPicoPions.size(); ++idxPion)
  
  //cout<<"done createCandidates"<<endl;

  return kStOK;
}

// _________________________________________________________
int StPicoLambdaAnaMaker::analyzeCandidates() {

  //cout<<"start analyzeCandidates"<<endl;
  // --- Analyze previously constructed pairs and save to ntuple
  // -- Decay channel1
  TClonesArray const * aCandidates= mPicoHFEvent->aHFSecondaryVertices();

  float ZDCx = mPicoDst->event()->ZDCx();
  float BBCx = mPicoDst->event()->BBCx();
  
  StPicoTrack const *lead_track = mPicoDst->track(mIdLeadingPart);
  StPicoTrack const *sublead_track = mPicoDst->track(mIdSubLeadingPart);
  
  lead_pt = lead_track->gPt();
  lead_eta = lead_track->gMom().PseudoRapidity();
  lead_phi = lead_track->gMom().Phi();
  
  sublead_pt = sublead_track->gPt();
  sublead_eta = sublead_track->gMom().PseudoRapidity();
  sublead_phi = sublead_track->gMom().Phi();

  if( mPicoHFEvent->nHFSecondaryVertices() > 0 )
  {
    for (unsigned int idx = 0; idx <  mPicoHFEvent->nHFSecondaryVertices(); ++idx)
    {
      StHFPair const* pair = static_cast<StHFPair*>(aCandidates->At(idx));

      if(pair->eta() == 0) continue;

      
      StPicoTrack const* part1 = mPicoDst->track(pair->particle1Idx()); //proton is the firs particle in the pair for Lambda
      StPicoTrack const* part2 = mPicoDst->track(pair->particle2Idx()); //pion is second particle in the pair for Lambda
      

      //TOF ---
      float part1BetaBase = -1;

      part1BetaBase = mHFCuts->getTofBetaBase(part1, mPicoDst->event()->bField());

      //get beta of track from TOF, if TOF information is available          
      p1_hasTOFinfo = 0;

      if(!isnan(part1BetaBase) && part1BetaBase > 0)
      {
        p1_hasTOFinfo = 1;      
      }


      //TOF ---
      float part2BetaBase = -1;

      part2BetaBase = mHFCuts->getTofBetaBase(part2, mPicoDst->event()->bField());

      //get beta of track from TOF, if TOF information is available          
      p2_hasTOFinfo = 0;

      if(!isnan(part2BetaBase) && part2BetaBase > 0)
      {
        p2_hasTOFinfo = 1;
      }

      //now checked in createCandidates()
      //if( mHFCuts->requireStrictTOF() && p2_hasTOFinfo == 0 ) continue; //strict TOF matching for pions, turned on/off in run macro
      
      // ---
      // Saving to TTree
      runId = mPicoHFEvent->runId();
      eventId = mPicoHFEvent->eventId();
      VzVzVPDmax = fabs(mPicoDst->event()->primaryVertex().z() - mPicoDst->event()->vzVpd());

      p1_pt  = part1->gPt();
      p1_phi = part1->gMom().Phi();
      p1_eta = part1->gMom(mPrimVtx,mBField).PseudoRapidity();
      p1_dca = part1->gDCAxy(mPrimVtx.x(), mPrimVtx.y());
      p1_ch = part1->charge();
      
      
      //eventId and runId common for all particles in the triplet
      p2_pt = part2->gPt();
      p2_phi = part2->gMom().Phi();
      p2_eta = part2->gMom(mPrimVtx,mBField).PseudoRapidity(); 
      p2_dca = part2->gDCAxy(mPrimVtx.x(), mPrimVtx.y());
      p2_ch = part2->charge();

      // -- Flag for like-sign or unlike-sign pairs
      pair_charge = -99;
      if( (part1->charge() + part2->charge()) == 0 ) pair_charge = 0; // unlike-sign - from decay of Lambda or K0s
      else if( fabs(part1->charge() + part2->charge()) == 2 ) pair_charge = 1; // unlike-sign - combinatorial background

      pair_DCAdaughters = pair->dcaDaughters();

      thetaProdPlane = pair->thetaProdPlane();

      prodPlane_x = pair->prodPlane().x();
      prodPlane_y = pair->prodPlane().y();
      prodPlane_z = pair->prodPlane().z();

      //cout<<pair->thetaProdPlane()<<endl;

      pair_theta = pair->pointingAngle();
      pair_cosThetaStar = pair->cosThetaStar();
      pair_decayL = pair->decayLength();
      pair_phi = pair->phi();
      pair_eta = pair->eta();
      pair_pt = pair->pt();
      pair_mass = pair->m();

      //fill tree
      //Lambdas and K0s stored in the same TClonesArray
      //need to check which one we extracted
      if(pair_mass > 0.8) ntp_Lambda->Fill();
      else ntp_K0s->Fill();

    } // for (unsigned int idx = 0; idx <  mPicoHFEvent->nHFSecondaryVertices(); ++idx) {
  }
  
  //cout<<"done analyzeCandidates"<<endl;

  return kStOK;
}

// _________________________________________________________
bool StPicoLambdaAnaMaker::isHadron(StPicoTrack const * const trk, int pidFlag) const {
  // -- good hadron
  return (mHFCuts->isGoodTrack(trk) && mHFCuts->isTPCHadron(trk, pidFlag));
}

// _________________________________________________________
bool StPicoLambdaAnaMaker::isPion(StPicoTrack const * const trk) const {
  // -- good pion

   TVector3 t = trk->gMom();
   if (!mHFCuts->hasGoodEta(t)) return false; 
   if (!mHFCuts->isHybridTOFHadron(trk, mHFCuts->getTofBetaBase(trk, mPicoDst->event()->bField()), StHFCuts::kPion) ) return false;
   if (!mHFCuts->cutMinDcaToPrimVertex(trk, StPicoCutsBase::kPion)) return false;
   return (mHFCuts->isGoodTrack(trk) && mHFCuts->isTPCHadron(trk, StPicoCutsBase::kPion));
}

// _________________________________________________________
bool StPicoLambdaAnaMaker::isKaon(StPicoTrack const * const trk) const {
  // -- good kaon

  TVector3 t = trk->gMom();
  if (!mHFCuts->hasGoodEta(t)) return false;
  if (!mHFCuts->isHybridTOFHadron(trk, mHFCuts->getTofBetaBase(trk, mPicoDst->event()->bField()), StHFCuts::kKaon) ) return false;
  if (!mHFCuts->cutMinDcaToPrimVertex(trk, StPicoCutsBase::kKaon)) return false;
  return (mHFCuts->isGoodTrack(trk) && mHFCuts->isTPCHadron(trk, StPicoCutsBase::kKaon));
}

// _________________________________________________________
bool StPicoLambdaAnaMaker::isProton(StPicoTrack const * const trk) const {
  // -- good proton
  TVector3 t = trk->gMom();
  if (!mHFCuts->hasGoodEta(t)) return false; 
  if (!mHFCuts->isHybridTOFHadron(trk, mHFCuts->getTofBetaBase(trk, mPicoDst->event()->bField()), StHFCuts::kProton) ) return false;
  if (!mHFCuts->cutMinDcaToPrimVertex(trk, StPicoCutsBase::kProton)) return false;
  return (mHFCuts->isGoodTrack(trk) && mHFCuts->isTPCHadron(trk, StPicoCutsBase::kProton));
}

double StPicoLambdaAnaMaker::DCA(StPicoTrack const * const trk, TVector3 const & vtx) const {
  // -- particle DCA

  return ((trk->origin() - vtx).Mag());
}


bool StPicoLambdaAnaMaker::isCloseTracks(StPicoTrack const * const trk1, StPicoTrack const * const trk2, TVector3 const & vtx, float bField) const {
  // -- good pair

  if( ( trk1->origin()-vtx ).Mag()>1.5 || ( trk2->origin()-vtx ).Mag()>1.5 ) return false;

  TVector3 const p1Mom = trk1->gMom();
  TVector3 const p2Mom = trk2->gMom();
  StPicoPhysicalHelix const p1StraightLine(p1Mom, trk1->origin(), 0, trk1->charge());
  StPicoPhysicalHelix const p2StraightLine(p2Mom, trk2->origin(), 0, trk2->charge());

  pair<double, double> const ss = p1StraightLine.pathLengths(p2StraightLine);
  TVector3 const p1AtDcaToP2 = p1StraightLine.at(ss.first);
  TVector3 const p2AtDcaToP1 = p2StraightLine.at(ss.second);
  float const dca = (p1AtDcaToP2-p2AtDcaToP1).Mag();

  if(dca > mHFCuts->cutSecondaryTripletDcaDaughters12Max()) return false; 

  return true;
}

//-----------------------------------------------------------------------------
