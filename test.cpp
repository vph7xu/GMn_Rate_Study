#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH1F.h"


class Draw{
public:
  void draw_pad1(TH1I* h1,TCanvas *c){
    c->cd(1);
    h1->Draw();
    gPad->Update();
  }

  void draw_pad1(TH2D* h1,TCanvas *c){
    c->cd(1);
    h1->Draw("COLZ");
    gPad->Update();
  }

  void draw_pad1d(TH1D* h1,TCanvas *c){
    c->cd(1);
    h1->Draw();
    gPad->Update();
  }

  void draw_pad1d_color(TH1D* h1, TH1D* h2, TH1D* h3, TH1D* h4, TCanvas *c){
    c->cd(1);
    h1->SetLineColor(kBlue);
    h2->SetLineColor(kRed);
    h3->SetLineColor(kGreen);
    h4->SetLineColor(kYellow);
    h1->Draw();
    h2->Draw("same");
    h3->Draw("same");
    h4->Draw("same");

    TLegend *legend = new TLegend(0.5, 0.7, 0.7, 0.9);
    legend->AddEntry(h1, "all", "l");
    legend->AddEntry(h2, "electron", "l");
    legend->AddEntry(h3, "muon", "l");
    legend->AddEntry(h4, "photon", "l");

    legend->Draw();

    gPad->Update();
  }

  void draw_pad1d_color(TH1D* h1, TH1D* h2, TCanvas *c){
    c->cd(1);
    h1->SetLineColor(kBlue);
    h2->SetLineColor(kRed);
    h1->Draw();
    h2->Draw("same");

    TAxis *xAxis = h1->GetXaxis();
    TAxis *yAxis = h1->GetYaxis();

    xAxis->SetTitle("Momentum(keV)");
    yAxis->SetTitle("Count");

    TLegend *legend = new TLegend(0.5, 0.7, 0.7, 0.9);
    legend->AddEntry(h1, "photon", "l");
    legend->AddEntry(h2, "other", "l");

    legend->Draw();

    gPad->Update();
  }

  void draw_pad5(TH2D *h1,TH2D *h2,TH2D *h3,TH2D *h4, TH2D *h5,TCanvas *c){
    c->cd(1);
    h1->Draw("COLZ");
    c->cd(2);
    h2->Draw("COLZ");
    c->cd(3);
    h3->Draw("COLZ");
    c->cd(4);
    h4->Draw("COLZ");
    c->cd(5);
    h5->Draw("COLZ");
    gPad->Update();
  }

  void draw_pad6(TH1D *h1,TH1D *h2,TH1D *h3,TH1D *h4, TH1D *h5, TH1D *h6, TCanvas *c){
    c->cd(1);
    h1->Draw();
    c->cd(2);
    h2->Draw();
    c->cd(3);
    h3->Draw();
    c->cd(4);
    h4->Draw();
    c->cd(5);
    h5->Draw();
    c->cd(6);
    h6->Draw();
    gPad->Update();
  }
};

/*void draw_pad4(TH1D *h1,TH1D *h2,TH1D *h3,TH1D *h4,TCanvas *c)
{
    c->cd(1);
    h1->Draw();
    c->cd(2);
    h2->Draw();
    c->cd(3);
    h3->Draw();
    c->cd(4);
    h4->Draw();
    gPad->Update();
}*/




void test(const char *file,int sbsconfig){
  //TFile *f = new TFile(file);
  //TTree *tree=(TTree*)f->Get("T");

  std::unique_ptr<TFile> f( TFile::Open(file) );
  auto T = f->Get<TTree>("T");

  
  T->SetMakeClass(1);
  //leaves 
  int Earm_BBGEM_hit_nhits=0;
  int Earm_BBGEM_track_ntracks=0;
  vector<double> *Earm_BBGEM_hit_edep = 0;
  vector<double> *Earm_BBGEM_hit_x=0;
  vector<double> *Earm_BBGEM_hit_y=0;
  vector<double> *Earm_BBGEM_hit_z=0;
  vector<double> *Earm_BBGEM_hit_p=0;

  vector<int> *Earm_BBGEM_hit_pid=0;
  vector<int> *Earm_BBGEM_hit_mid=0;
  vector<int> *Earm_BBGEM_track_pid=0;
  

  double ev_ep=0; //initial electron momentum
  //Double_t ev_count = 0;
  vector<double> *Earm_BBGEM_track_x=0;
  vector<double> *Earm_BBGEM_track_y=0;


  double energy_dep [6] = {};


  //branches
  TBranch *b_Earm_BBGEM_hit_edep;

  TBranch *b_Earm_BBGEM_hit_nhits;
  TBranch *b_Earm_BBGEM_track_ntracks=0;
  TBranch *b_Earm_BBGEM_hit_x;
  TBranch *b_Earm_BBGEM_hit_y;
  TBranch *b_Earm_BBGEM_hit_z;
  TBranch *b_Earm_BBGEM_hit_p;
  TBranch *b_Earm_BBGEM_hit_pid;
  TBranch *b_Earm_BBGEM_track_pid;
  TBranch *b_Earm_BBGEM_hit_mid;
  TBranch *b_ev;

  TBranch *b_Earm_BBGEM_track_numhits;
  TBranch *b_Earm_BBGEM_track_x;
  TBranch *b_Earm_BBGEM_track_y;
  //TBranch *b_Earm_BBGEM_track_z;


  //branch addresses
  T->SetBranchAddress("Earm.BBGEM.hit.edep",&Earm_BBGEM_hit_edep);
  T->SetBranchAddress("Earm.BBGEM.hit.nhits",&Earm_BBGEM_hit_nhits);//,&b_Earm_BBGEM_hit_nhits);
  T->SetBranchAddress("Earm.BBGEM.Track.ntracks",&Earm_BBGEM_track_ntracks);
  T->SetBranchAddress("Earm.BBGEM.hit.x",&Earm_BBGEM_hit_x);//,&b_Earm_BBGEM_hit_x);
  T->SetBranchAddress("Earm.BBGEM.hit.y",&Earm_BBGEM_hit_y);//,&b_Earm_BBGEM_hit_y);
  T->SetBranchAddress("Earm.BBGEM.hit.z",&Earm_BBGEM_hit_z);
  T->SetBranchAddress("Earm.BBGEM.hit.p",&Earm_BBGEM_hit_p);
  T->SetBranchAddress("Earm.BBGEM.Track.X",&Earm_BBGEM_track_x);
  T->SetBranchAddress("Earm.BBGEM.Track.Y",&Earm_BBGEM_track_y);
  T->SetBranchAddress("Earm.BBGEM.hit.pid",&Earm_BBGEM_hit_pid);
  T->SetBranchAddress("Earm.BBGEM.hit.mid",&Earm_BBGEM_hit_mid);
  T->SetBranchAddress("Earm.BBGEM.Track.PID",&Earm_BBGEM_track_pid);
  //T->SetBranchAddress("ev",&ev_);
  //T->SetBranchAddress("ev->count",&ev_count);//,&b_ev);
  
  int nentries = T->GetEntries();
  std::cout<<"number of entries : "<<nentries <<endl;


  //define histograms
  TH1I *hnhits = new TH1I("hnhits","number of hits",15,0,15);
  TH1I *hntracks = new TH1I("hntracks","number of tracks",10,0,10);

  TH1D *hedepBBGEML0 = new TH1D("edep0","energy deposited L0",5000,0,0.00005);
  TH1D *hedepBBGEML1 = new TH1D("edep1","energy deposited L1",5000,0,0.00005);
  TH1D *hedepBBGEML2 = new TH1D("edep2","energy deposited L2",5000,0,0.00005);
  TH1D *hedepBBGEML3 = new TH1D("edep3","energy deposited L3",5000,0,0.00005);
  TH1D *hedepBBGEML4 = new TH1D("edep4","energy deposited L4",5000,0,0.00005);
  TH1D *hedepBBGEMAll = new TH1D("edepAll","energy deposited All",5000,0,0.00005);

  TH1D *hedepelec = new TH1D("edepelec","energy deposited by electrons", 5000,0,0.00005);
  TH1D *hedepmuon = new TH1D("edepmuon","energy deposited by muon",5000,0,0.00005);
  TH1D *hedepgamma = new TH1D("edepgamma","energy deposited by gamma",5000,0,0.00005);
  TH1D *hedepother = new TH1D("edepother","energy deposited by other",5000,0,0.00005);

  TH1I *hpid = new TH1I("pid","particle ID",100, -50, 50);
  TH1I *hmid = new TH1I("mid","mother particle ID",100,-50,50);
  TH1I *hTpid = new TH1I("tpid","Track PID", 200, -100, 100);
  
  TH2D *h2dmap_l0 = new TH2D("h2dmap_l0","Hit Map L0",300,-1.5,1.5,50,-0.5,0.5);
  TH2D *h2dmap_l1 = new TH2D("h2dmap_l1","Hit Map L1",300,-1.5,1.5,50,-0.5,0.5);
  TH2D *h2dmap_l2 = new TH2D("h2dmap_l2","Hit Map L2",300,-1.5,1.5,50,-0.5,0.5);
  TH2D *h2dmap_l3 = new TH2D("h2dmap_l3","Hit Map L3",300,-1.5,1.5,50,-0.5,0.5);
  TH2D *h2dmap_l4 = new TH2D("h2dmap_l4","Hit Map L4",300,-1.5,1.5,50,-0.5,0.5);
  TH2D *htrack_z0 = new TH2D("htrack_z0","Track position at z=0",300,-1.5,1.5,50,-0.5,0.5);

  TH1D *hx = new TH1D("hx","hit_x",100,-1.0,1.0);
  TH1D *hy = new TH1D("hx","hit_y",50,-0.5,0.5);
  TH1D *hz = new TH1D("hx","hit_z",200,-0.1,2.0);
  TH1D *htx = new TH1D("htx","track_x",100,-1.0,1.0);
  TH1D *hty = new TH1D("hty","track_y",50,-0.5,0.5);
  TH1D *hp_photon_L0 = new TH1D("hp_ph","hit_p_photon",10000,0,5000);
  TH1D *hp_other_L0 = new TH1D("hp_other","hit_p_other",10000,0,5000);
 

  TH1D *hevep = new TH1D("hevep","Inital electron momentum",100,1.0,3.0);

  //test
  T->Scan("Earm.BBGEM.hit.nhits:Earm.BBGEM.hit.x:Earm.BBGEM.hit.y:Earm.BBGEM.hit.z:ev.ep");

  int mip_count_L0 =0;
  
  for (int ientry = 0; ientry<nentries;ientry++){
    T->GetEntry(ientry);
    int nhits = Earm_BBGEM_hit_nhits;
    int ntracks = Earm_BBGEM_track_ntracks;
    double evep = T->GetLeaf("ev.ep")->GetValue(0);

    hnhits->Fill(nhits);
    hevep->Fill(evep);
    hntracks->Fill(ntracks);
    

    int nx = Earm_BBGEM_hit_x->size();
    int ny = Earm_BBGEM_hit_y->size();
    int nz = Earm_BBGEM_hit_z->size();
    int np = Earm_BBGEM_hit_p->size();
    int ntx = Earm_BBGEM_track_x->size();
    int nty = Earm_BBGEM_track_y->size();
    int nedep = Earm_BBGEM_hit_edep->size();
    int npid = Earm_BBGEM_hit_pid->size();

    double *x = Earm_BBGEM_hit_x->data();
    double *y = Earm_BBGEM_hit_y->data();
    double *z = Earm_BBGEM_hit_z->data();
    double *p = Earm_BBGEM_hit_p->data();
    double *tx = Earm_BBGEM_track_x->data();
    double *ty = Earm_BBGEM_track_y->data();
    int *pid = Earm_BBGEM_hit_pid->data();
    int *mid = Earm_BBGEM_hit_mid->data();
    int *tpid = Earm_BBGEM_track_pid->data();

    double *edep = Earm_BBGEM_hit_edep->data();


    if (ientry%10000 == 0) std::cout<<ientry<<" : "<<nhits<<" : "<<evep<<" nz : "<<nz/*<<" z : "<< z[0]<<" pid :" <<pid[0]*/<<endl;

    for (int i = 0; i < nhits; i++){
      hx->Fill(x[i]);
      hy->Fill(y[i]);
      hz->Fill(z[i]);
      
      hedepBBGEMAll->Fill(edep[i]);
      if(pid[i] == 11) hedepelec->Fill(edep[i]);
      else if (pid[i] == 13) hedepmuon->Fill(edep[i]);
      else if (pid[i] == 22) {
	      hedepgamma->Fill(edep[i]);
      	      //hp_photon->Fill(p[i]);
      }
      else hedepother->Fill(edep[i]);

      hpid->Fill(pid[i]);
      hmid->Fill(mid[i]);
      if (z[i]<=0.1){
        h2dmap_l0->Fill(x[i],y[i]);
        hedepBBGEML0->Fill(edep[i]);
	
	if (pid[i] == 22){
	  hp_photon_L0->Fill(p[i]*1000000);
	}
	else{
	  hp_other_L0->Fill(p[i]*1000000);
	}

        if (edep[i]>0.0000006){
          mip_count_L0+=1;
        }
      }
      else if(z[i]<=0.2){
        h2dmap_l1->Fill(x[i],y[i]);
        hedepBBGEML1->Fill(edep[i]);
      }
      else if(z[i]<=0.3){
        h2dmap_l2->Fill(x[i],y[i]);
        hedepBBGEML2->Fill(edep[i]);
      }
      else if(z[i]<=0.5){
        h2dmap_l3->Fill(x[i],y[i]);
        hedepBBGEML3->Fill(edep[i]);
      }
      else if(z[i]<=1.6){
        h2dmap_l4->Fill(x[i],y[i]);
        hedepBBGEML4->Fill(edep[i]);
      }
    }

    for (int i=0; i < ntracks; i++){
      htx->Fill(tx[i]);
      hty->Fill(ty[i]);
      htrack_z0->Fill(tx[i],ty[i]);
      hTpid->Fill(tpid[i]);
    }
  }


  energy_dep[0] = hedepBBGEML0->GetMean() * hedepBBGEML0->GetEntries();
  energy_dep[1] = hedepBBGEML1->GetMean() * hedepBBGEML1->GetEntries();
  energy_dep[2] = hedepBBGEML2->GetMean() * hedepBBGEML2->GetEntries();
  energy_dep[3] = hedepBBGEML3->GetMean() * hedepBBGEML3->GetEntries();
  energy_dep[4] = hedepBBGEML4->GetMean() * hedepBBGEML4->GetEntries();
  energy_dep[5] = hedepBBGEMAll->GetMean() * hedepBBGEMAll->GetEntries();

  std::cout<<"Total Energy deposited L0,L1,L2,L3,and L4 : "<<energy_dep[0]<<" , "<<energy_dep[1]<<" , "<<energy_dep[2]<<" , "<<energy_dep[3]<<" , "<<energy_dep[4]<<endl;
  std::cout<<"Sum of Energy deposited in all layers : "<<energy_dep[5]<<endl;
  std::cout<<"Mip count at L0 : "<<mip_count_L0<<endl;

  //define canvas
  TCanvas *c = new TCanvas("c","c",1900,1000);
  TCanvas *c1 = new TCanvas("c1","c1",1900,1000);
  TCanvas *c2 = new TCanvas("c2","c2",1900,1000);
  TCanvas *c3 = new TCanvas("c3","c3",1900,1000);
  TCanvas *c4 = new TCanvas("c4","c4",1900,1000);
  TCanvas *c5 = new TCanvas("c5","c5",1900,1000);
  TCanvas *c6 = new TCanvas("c6","c6",1900,1000);
  TCanvas *c7 = new TCanvas("c7","c7",1900,1000);
  TCanvas *c8 = new TCanvas("c8","c8",1900,1000);
  TCanvas *c9 = new TCanvas("c9","c9",1900,1000);
  TCanvas *c10 = new TCanvas("c10","c10",1900,1000);
  TCanvas *c11 = new TCanvas("c11","c11",1900,1000); 
  TCanvas *c12 = new TCanvas("c12","c12",1900,1000);
  TCanvas *c13 = new TCanvas("c13","c13",1900,1000);
  TCanvas *c14 = new TCanvas("c14","c14",1900,1000);
  TCanvas *c15 = new TCanvas("c15","c15",1900,1000);
  //TCanvas *c15 = new TCanvas("c15","c15",1900,1000);

  //adding text to a canvas; have to write a function for this ...

  Draw D;
  
  c->Divide(3,2);
  c1->Divide(1,1);
  c2->Divide(1,1);
  c3->Divide(1,1);
  c4->Divide(1,1);
  c5->Divide(1,1);
  c6->Divide(1,1);
  c7->Divide(1,1);
  c8->Divide(1,1);
  c9->Divide(1,1);
  c10->Divide(3,2);
  c11->Divide(1,1);
  c12->Divide(1,1);
  c13->Divide(1,1);
  c15->Divide(1,1);

  D.draw_pad1(hnhits,c1);
  D.draw_pad1(hntracks,c6);
  D.draw_pad1d(hx,c2);
  D.draw_pad1d(hy,c3);
  D.draw_pad1d(hz,c4);
  D.draw_pad1d(hevep,c5);
  D.draw_pad1d(htx,c7);
  D.draw_pad1d(hty,c8);
  D.draw_pad1(htrack_z0,c9);
  D.draw_pad6(hedepBBGEML0,hedepBBGEML1,hedepBBGEML2,hedepBBGEML3,hedepBBGEML4,hedepBBGEMAll,c10);
  D.draw_pad1(hpid,c11);
  D.draw_pad1(hTpid,c12);
  D.draw_pad1(hpid,c13);
  D.draw_pad1d_color(hedepBBGEMAll,hedepelec,hedepmuon,hedepgamma,c14);
  D.draw_pad1d_color(hp_photon_L0,hp_other_L0,c15);


  D.draw_pad5(h2dmap_l0,h2dmap_l1,h2dmap_l2,h2dmap_l3,h2dmap_l4,c);

  c->Draw();
  c1->Draw();
  c2->Draw();
  c3->Draw();
  c4->Draw();
  c5->Draw();
  c6->Draw();
  c7->Draw();
  c8->Draw();
  c9->Draw();
  c10->Draw();
  c11->Draw();
  c12->Draw();
  c13->Draw();
  c15->Draw();

  using namespace std;

  const char *filename = Form("Plots/SBS%d_bkg.pdf(",sbsconfig);
  const char *filename1 = Form("Plots/SBS%d_bkg.pdf",sbsconfig);
  const char *filename2 = Form("Plots/SBS%d_bkg.pdf)",sbsconfig); 
   
  c1->Print(filename);
  c2->Print(filename1);    
  c3->Print(filename1);
  c4->Print(filename1);
  c5->Print(filename1);
  c->Print(filename1);
  c6->Print(filename1);
  c7->Print(filename1);
  c8->Print(filename1);
  c9->Print(filename1);
  c11->Print(filename1);
  c12->Print(filename1);
  c13->Print(filename1);
  c15->Print(filename1);  
  c10->Print(filename2);

}
