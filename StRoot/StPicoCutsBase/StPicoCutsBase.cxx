#include <limits>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>

#include "StPicoCutsBase.h"

#include "TLorentzVector.h"
#include "TVector3.h"
#include "StPicoEvent/StPicoPhysicalHelix.h"

#include "phys_constants.h"
#include "SystemOfUnits.h"
#include "StBTofUtil/tofPathLength.hh"

#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoTrack.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StPicoEvent/StPicoBTofPidTraits.h"

ClassImp(StPicoCutsBase)

// _________________________________________________________
StPicoCutsBase::StPicoCutsBase() : TNamed("PicoCutsBase", "PicoCutsBase"), 
  mTOFCorr(new StV0TofCorrection), mPicoDst(NULL), mEventStatMax(6), mTOFResolution(0.013),
  mBadRunListFileName("picoList_bad_MB.list"), mVzMax(6.), mVzVpdVzMax(3.), 
  mNHitsFitMin(20), mRequireHFT(true), mNHitsFitnHitsMax(0.52), mPrimaryDCAtoVtxMax(1.0) {
  
  // -- default constructor
  
  for (Int_t idx = 0; idx < kPicoPIDMax; ++idx) {
    mPtRange[idx][0] = std::numeric_limits<float>::lowest();
    mPtRange[idx][1] = std::numeric_limits<float>::max();
    mDcaMin[idx] = std::numeric_limits<float>::lowest();
    mDcaMinTertiary[idx] = std::numeric_limits<float>::lowest();
    mPtotRangeTOF[idx][0] = std::numeric_limits<float>::lowest();
    mPtotRangeTOF[idx][1] = std::numeric_limits<float>::max();
    mPtotRangeHybridTOF[idx][0] = std::numeric_limits<float>::lowest();
    mPtotRangeHybridTOF[idx][1] = std::numeric_limits<float>::max();
    mTPCNSigmaMax[idx] = std::numeric_limits<float>::max();
    mTOFDeltaOneOverBetaMax[idx] = std::numeric_limits<float>::max();
  }
  
  mHypotheticalMass[kPion]      = M_PION_PLUS;
  mHypotheticalMass2[kPion]     = M_PION_PLUS*M_PION_PLUS;
  mHypotheticalMass[kKaon]      = M_KAON_PLUS;
  mHypotheticalMass2[kKaon]     = M_KAON_PLUS*M_KAON_PLUS;
  mHypotheticalMass[kProton]    = M_PROTON;
  mHypotheticalMass2[kProton]   = M_PROTON*M_PROTON;
  mHypotheticalMass[kElectron]  = M_ELECTRON;
  mHypotheticalMass2[kElectron] = M_ELECTRON*M_ELECTRON;
  mHypotheticalMass[kMuon]      = M_MUON_PLUS;
  mHypotheticalMass2[kMuon]     = M_MUON_PLUS*M_MUON_PLUS;
  mHypotheticalMass[kK0Short]   = M_KAON_0_SHORT;
  mHypotheticalMass2[kK0Short]  = M_KAON_0_SHORT*M_KAON_0_SHORT;
  mHypotheticalMass[kLambda]    = M_LAMBDA;
  mHypotheticalMass2[kLambda]   = M_LAMBDA*M_LAMBDA;
}

// _________________________________________________________
StPicoCutsBase::StPicoCutsBase(const Char_t *name) : TNamed(name, name), 
  mTOFCorr(new StV0TofCorrection), mPicoDst(NULL), mEventStatMax(7), mTOFResolution(0.013),
  mBadRunListFileName("picoList_bad_MB.list"), mVzMax(6.), mVzVpdVzMax(3.),
  mNHitsFitMin(20), mRequireHFT(true), mNHitsFitnHitsMax(0.52), mPrimaryDCAtoVtxMax(1.0) {
  // -- constructor

  for (Int_t idx = 0; idx < kPicoPIDMax; ++idx) {
    mPtRange[idx][0] = std::numeric_limits<float>::lowest();
    mPtRange[idx][1] = std::numeric_limits<float>::max();
    mDcaMin[idx] = std::numeric_limits<float>::lowest();
    mDcaMinTertiary[idx] = std::numeric_limits<float>::lowest();
    mPtotRangeTOF[idx][0] = std::numeric_limits<float>::lowest();
    mPtotRangeTOF[idx][1] = std::numeric_limits<float>::max();
    mPtotRangeHybridTOF[idx][0] = std::numeric_limits<float>::lowest();
    mPtotRangeHybridTOF[idx][1] = std::numeric_limits<float>::max();
    mTPCNSigmaMax[idx] = std::numeric_limits<float>::max();
    mTOFDeltaOneOverBetaMax[idx] = std::numeric_limits<float>::max();
  }

  mHypotheticalMass[kPion]      = M_PION_PLUS;
  mHypotheticalMass2[kPion]     = M_PION_PLUS*M_PION_PLUS;
  mHypotheticalMass[kKaon]      = M_KAON_PLUS;
  mHypotheticalMass2[kKaon]     = M_KAON_PLUS*M_KAON_PLUS;
  mHypotheticalMass[kProton]    = M_PROTON;
  mHypotheticalMass2[kProton]   = M_PROTON*M_PROTON;
  mHypotheticalMass[kElectron]  = M_ELECTRON;
  mHypotheticalMass2[kElectron] = M_ELECTRON*M_ELECTRON;
  mHypotheticalMass[kMuon]      = M_MUON_PLUS;
  mHypotheticalMass2[kMuon]     = M_MUON_PLUS*M_MUON_PLUS;
  mHypotheticalMass[kK0Short]   = M_KAON_0_SHORT;
  mHypotheticalMass2[kK0Short]  = M_KAON_0_SHORT*M_KAON_0_SHORT;
  mHypotheticalMass[kLambda]    = M_LAMBDA;
  mHypotheticalMass2[kLambda]   = M_LAMBDA*M_LAMBDA;

}
// _________________________________________________________
StPicoCutsBase::~StPicoCutsBase() { 
  // destructor
  
  if (mTOFCorr)
    delete mTOFCorr;
  mTOFCorr = NULL;
}

// _________________________________________________________
void StPicoCutsBase::initBase() {
  // -- init cuts class

  // -- Read in bad run list and fill vector
  // -----------------------------------------

  // -- open list
  ifstream runs;

  // -- open in working dir
  runs.open(mBadRunListFileName.Data());
  if (!runs.is_open()) {
    runs.open(Form("picoLists/%s", mBadRunListFileName.Data()));
    if (!runs.is_open()) {
      cout << "StPicoCutsBase::initBase -- Bad run list NOT found :" << mBadRunListFileName << endl;
      cout << "StPicoCutsBase::initBase -- continue without bad run selection! " << endl;
      //exit(EXIT_FAILURE);
    }
  }

  if (runs.is_open()) {
    Int_t runId = 0;
    while( runs >> runId )
      mVecBadRunList.push_back(runId);
    
    runs.close();

    // -- sort bad runs vector
    std::sort(mVecBadRunList.begin(), mVecBadRunList.end());
  }
}

// _________________________________________________________
bool StPicoCutsBase::isGoodEvent(StPicoDst const * const picoDst, int *aEventCuts) {
  // -- method to check if good event
  //    sets also mPicoDst and mPrimVtx
  
  // -- set current mPicoDst 
  mPicoDst = picoDst;

  // -- get picoDst event
  StPicoEvent* picoEvent = mPicoDst->event();

  // -- set current primary vertex
  mPrimVtx = picoEvent->primaryVertex();

  // -- quick method without providing stats
  if (!aEventCuts) 
  {	
		return (isGoodRun(picoEvent) && isGoodTrigger(picoEvent) &&
		       fabs(picoEvent->primaryVertex().z()) < mVzMax &&
    		   fabs(picoEvent->primaryVertex().z() - picoEvent->vzVpd()) < mVzVpdVzMax );		
  }
    
  // -- reset event cuts
  for (unsigned int ii = 0; ii < mEventStatMax; ++ii)
    aEventCuts[ii] = 0;
  
  unsigned int iCut = 0;

  // -- 0 - before event cuts
  aEventCuts[iCut] = 0;

  // -- 1 - is bad run
  ++iCut;
	if (!isGoodRun(picoEvent))
    aEventCuts[iCut] = 1;


  // -- 2 - No Trigger fired
  ++iCut;
  if (!isGoodTrigger(picoEvent))
    aEventCuts[iCut] = 1;

  // -- 3 - Vertex z outside cut window
  ++iCut;
  if (fabs(picoEvent->primaryVertex().z()) >= mVzMax)
    aEventCuts[iCut] = 1;

  // -- 4 Vertex z - vertex_z(vpd) outside cut window
  ++iCut;
  if (fabs(picoEvent->primaryVertex().z() - picoEvent->vzVpd()) >= mVzVpdVzMax)
    aEventCuts[iCut] = 1;  
  
  // -- 5 Vx and Vy error
//  ++iCut;
//  if(  picoEvent->primaryVertexError().x() > mVxErrMax || picoEvent->primaryVertexError().y() > mVyErrMax )
//    aEventCuts[iCut] = 1;
  // ... if needed

  // -- is rejected
  bool isGoodEvent = true;
  for (unsigned int ii = 0; ii < mEventStatMax; ++ii)
    if  (aEventCuts[ii])
      isGoodEvent = false;
        
  return isGoodEvent;
}
// _________________________________________________________

bool StPicoCutsBase::isGoodRun(StPicoEvent const * const picoEvent) const {
  // -- is good run (not in bad runlist)

  return (!(std::binary_search(mVecBadRunList.begin(), mVecBadRunList.end(), picoEvent->runId())));
}
// _________________________________________________________

bool StPicoCutsBase::isGoodTrigger(StPicoEvent const * const picoEvent) const {
  // -- is good trigger in list of good triggerIds
  return true;
  //check if the event cotains any triggerId we dont't want first
  for(std::vector<unsigned int>::const_iterator iter = mVecBadTriggerIdList.begin(); iter != mVecBadTriggerIdList.end(); ++iter)
  {
    if(picoEvent->isTrigger(*iter))
    {
      return false;
    }  
  }

  //now check for triggerIds we want
  for(std::vector<unsigned int>::const_iterator iter = mVecTriggerIdList.begin(); iter != mVecTriggerIdList.end(); ++iter)
  {
    if(picoEvent->isTrigger(*iter))
    {
      return true;
    }  
  }
   

  return false;
}
// _________________________________________________________

bool StPicoCutsBase::isGoodTrack(StPicoTrack const * const trk) const {
  // -- require at least one hit on every layer of PXL and (IST or SSD).
  return ((!mRequireHFT || trk->isHFTTrack()) && 
          hasGoodEta(trk->gMom()) &&
          trk->gPt() > mPtMin &&
	        trk->nHitsFit() >= mNHitsFitMin &&
          (float)trk->nHitsFit()/(float)trk->nHitsMax() >= mNHitsFitnHitsMax  );
}

// =======================================================================

// _________________________________________________________
bool StPicoCutsBase::cutMinDcaToPrimVertex(StPicoTrack const * const trk, int pidFlag) const {
  // -- check on min dca for identified particle

  //new SL16j Vanek
  float dca = (mPrimVtx - trk->origin()).Mag(); //origin computed inside StPicoTrack

  return (dca >= mDcaMin[pidFlag]);
}

// _________________________________________________________
bool StPicoCutsBase::cutMinDcaToPrimVertexTertiary(StPicoTrack const * const trk, int pidFlag) const {
  // -- check on min dca for identified particle - used for tertiary particles only

  //new SL16j Vanek
  float dca = (mPrimVtx - trk->origin()).Mag(); //origin computed inside StPicoTrack

  return (dca >= mDcaMin[pidFlag]);
}

// =======================================================================

// _________________________________________________________
bool StPicoCutsBase::isTPCHadron(StPicoTrack const * const trk, int pidFlag) const {
  // -- check for good hadron in TPC

  float nSigma = std::numeric_limits<float>::quiet_NaN();

  if (pidFlag == kPion)
    nSigma = fabs(trk->nSigmaPion());
  else if (pidFlag == kKaon)
    nSigma = fabs(trk->nSigmaKaon());
  else if (pidFlag == kProton)
    nSigma = fabs(trk->nSigmaProton());

  return ( trk->gPt() >= mPtRange[pidFlag][0] && trk->gPt() < mPtRange[pidFlag][1] &&
	   nSigma < mTPCNSigmaMax[pidFlag] );
}

// _________________________________________________________
bool StPicoCutsBase::hasGoodTPCnSigma(StPicoTrack const *trk, int pidFlag) const {
  // -- check for good nSigma of hadron in TPC

  float nSigma = std::numeric_limits<float>::quiet_NaN();

  if (pidFlag == kPion)
    nSigma = fabs(trk->nSigmaPion());
  else if (pidFlag == kKaon)
    nSigma = fabs(trk->nSigmaKaon());
  else if (pidFlag == kProton)
    nSigma = fabs(trk->nSigmaProton());

  return ( nSigma < mTPCNSigmaMax[pidFlag] );
}
// _________________________________________________________

bool StPicoCutsBase::hasGoodEta(TVector3 const & trkMom) const {
	return ( fabs(trkMom.PseudoRapidity()) <= mEta );
}
// _________________________________________________________

bool StPicoCutsBase::isTOFHadronPID(StPicoTrack const *trk, float const & tofBeta, int pidFlag) const {
  // -- check for good hadron in TOF PID
  //    use for 
  //      - primary hadrons 
  //      - secondarys from charm decays (as an approximation)
  //    return:
  //      no TOF info : false
  
  // -- has TOF information
  if (tofBeta <= 0) 
    return false;
  
	float ptot    = trk->gPtot(); //SL16j, Vanek
  float betaInv = sqrt(ptot*ptot + mHypotheticalMass2[pidFlag]) / ptot;
  return ( fabs(1/tofBeta - betaInv) < mTOFDeltaOneOverBetaMax[pidFlag] );
}

// _________________________________________________________
bool StPicoCutsBase::isTOFHadron(StPicoTrack const *trk, float const & tofBeta, int pidFlag) const {
  // -- check for good hadron in TOF in ptot range
  //    use for 
  //      - primary hadrons 
  //      - secondarys from charm decays (as an approximation)
  //    return:
  //      not in ptot range : true

  // -- only apply, if in ptot range

	float ptot = trk->gPtot(); //SL16j, Vanek
  if (ptot < mPtotRangeTOF[pidFlag][0] || ptot >= mPtotRangeTOF[pidFlag][1])
    return true;

  return isTOFHadronPID(trk, tofBeta, pidFlag);
}

// _________________________________________________________
bool StPicoCutsBase::isHybridTOFHadron(StPicoTrack const *trk, float const & tofBeta, int pidFlag) const {
  // -- check for good hadron in TOF in ptot range
  //    use for 
  //      - primary hadrons 
  //      - secondarys from charm decays (as an approximation)
  //    return:
  //      not in ptot range : true
  //      no TOF info       : true

  // -- only apply, if in ptot range

	float ptot = trk->gPtot(); //SL16j, Vanek
  if (ptot < mPtotRangeHybridTOF[pidFlag][0] || ptot >= mPtotRangeHybridTOF[pidFlag][1])
    return true;

  // -- only apply, if has TOF information
  if (tofBeta <= 0 || tofBeta != tofBeta ) 
    return true;

  return isTOFHadronPID(trk, tofBeta, pidFlag);
}

// =======================================================================

// _________________________________________________________
StPicoBTofPidTraits* StPicoCutsBase::hasTofPid(StPicoTrack const * const trk) const {
  // -- check if track has TOF pid information
  //    return NULL otherwise

  int index2tof = trk->bTofPidTraitsIndex();
  return (index2tof >= 0) ? mPicoDst->btofPidTraits(index2tof) : NULL;
}

// _________________________________________________________
float StPicoCutsBase::getTofBetaBase(StPicoTrack const * const trk, float B) const { //new argument for magnetic field "float B", SL16j, Vanek
  // -- provide beta of TOF for pico track
  //    use for 
  //      - primary hadrons 
  //      - secondarys from charm decays (as an approximation)

  float beta = std::numeric_limits<float>::quiet_NaN();

  StPicoBTofPidTraits *tofPid = hasTofPid(trk);
  if (!tofPid) 
    return beta;

  beta = tofPid->btofBeta();
  if (beta < 1e-4) {
    TVector3 const btofHitPos = tofPid->btofHitPos(); 
		StPicoPhysicalHelix helix = trk->helix(B); //SL16j, Vanek
    float pathLength = tofPathLength(&mPrimVtx, &btofHitPos, helix.curvature());
    float tof = tofPid->btof();
    beta = (tof > 0) ? pathLength / (tof * (C_C_LIGHT / 1.e9)) : std::numeric_limits<float>::quiet_NaN();
  }
    
  return beta;
}

// _________________________________________________________
float StPicoCutsBase::getTofBeta(StPicoTrack const * const trk, float B) const { //new argument for magnetic field "float B", SL16j, Vanek
  // -- provide beta of TOF for pico track
  //    use for 
  //      - primary hadrons 
  //      - secondarys from charm decays (as an approximation)
  //    -> apply DCA cut to primary vertex to make sure only primaries or secondary HF decays are used

	return ((trk->origin() - mPrimVtx).Mag() < mPrimaryDCAtoVtxMax) ? getTofBetaBase(trk, B) : std::numeric_limits<float>::quiet_NaN(); //SL16j, Vanek
}


// _________________________________________________________
float StPicoCutsBase::getTofBeta(StPicoTrack const * const trk, 
				 TLorentzVector const & secondaryMother, TVector3 const & secondaryVtx, float B) const {
  // -- provide correced beta of TOF for pico track
  //    use for 
  //      - secondaries

  float beta = std::numeric_limits<float>::quiet_NaN();

  StPicoBTofPidTraits *tofPid = hasTofPid(trk);
  if (!tofPid) 
    return beta;

  TVector3 tofHit = tofPid->btofHitPos();


  // -- set waypoints
  mTOFCorr->setVectors3D(mPrimVtx)(secondaryVtx)(tofHit);

  // -- set mother track
  mTOFCorr->setMotherTracks(secondaryMother);
  
  float tof = tofPid->btof();
	StPicoPhysicalHelix helix = trk->helix(B); //problem - cannot convert StPicoPhysicalHelix to StPhysicalHelixD
  
  // -- correct beta
  mTOFCorr->correctBeta(helix, tof, beta);

  // -- clean up
  mTOFCorr->clearContainers();
  
  return beta;
}

// _________________________________________________________
float StPicoCutsBase::getTofBeta(StPicoTrack const * const trk, 
				 TLorentzVector const & secondaryMother, TVector3 const & secondaryVtx, 
				 TLorentzVector const & tertiaryMother,  TVector3 const & tertiaryVtx,
					float B) const {
  // -- provide correced beta of TOF for pico track
  //    use for 
  //      - tertiaries 

  float beta = std::numeric_limits<float>::quiet_NaN();

  StPicoBTofPidTraits *tofPid = hasTofPid(trk);
  if (!tofPid) 
    return beta;

  TVector3 tofHit = tofPid->btofHitPos();

  // -- set waypoints
  mTOFCorr->setVectors3D(mPrimVtx)(secondaryVtx)(tertiaryVtx)(tofHit);

  // -- set mother track
  mTOFCorr->setMotherTracks(secondaryMother)(tertiaryMother);
  
  float tof = tofPid->btof();
	StPicoPhysicalHelix helix = trk->helix(B); //SL16j, Vanek
  
  // -- correct beta
  mTOFCorr->correctBeta(helix, tof, beta);

  // -- clean up
  mTOFCorr->clearContainers();
  
  return beta;
}

