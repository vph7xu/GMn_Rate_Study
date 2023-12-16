#define MAX_HITS 3000

class GEMHitTree{
public :
	TTree *fChain;
	Int_t fCurrent;

	//int max_hits = 1000;
        //declaration of leaf types
        //Int_t Earm_;
        //Int_t Earm_BBGEM_;
        //Int_t Earm_BBGEM_hit_;
        Int_t Earm_BBGEM_hit_nhits=0;
        Double_t Earm_BBGEM_hit_x[MAX_HITS];
        Double_t Earm_BBGEM_hit_y[MAX_HITS];

        //List of branches
        //TBranch *b_Earm_;
        //TBranch *b_Earm_BBGEM_;
        //TBranch *b_Earm_BBGEM_hit_;
        TBranch *b_Earm_BBGEM_hit_nhits;
        TBranch *b_Earm_BBGEM_hit_x;
        TBranch *b_Earm_BBGEM_hit_y;

	GEMHitTree(TTree *tree=0);
	virtual ~GEMHitTree();
//	virtual void Init(TTree *tree);
};

GEMHitTree::GEMHitTree(TTree*tree):fChain(0){}

GEMHitTree::~GEMHitTree(){}

void Init(TTree *tree){

	GEMHitTree gemhittree;

	gemhittree.fChain = tree;
        gemhittree.fCurrent = -1;
        gemhittree.fChain->SetMakeClass(1);

        //Set branch addresses and branch pointers
        std::cout<<"0-pass"<<endl;
        gemhittree.fChain->SetBranchAddress("Earm.BBGEM.hit.nhits",&gemhittree.Earm_BBGEM_hit_nhits,&gemhittree.b_Earm_BBGEM_hit_nhits);
        std::cout<<"00-pass"<<endl;
        gemhittree.fChain->SetBranchAddress("Earm.BBGEM.hit.x",&gemhittree.Earm_BBGEM_hit_x,&gemhittree.b_Earm_BBGEM_hit_x);
        std::cout<<"000-pass"<<endl;
        gemhittree.fChain->SetBranchAddress("Earm.BBGEM.hit.y",&gemhittree.Earm_BBGEM_hit_y,&gemhittree.b_Earm_BBGEM_hit_y);
        std::cout<<"0000-pass"<<endl;
        gemhittree.fChain->GetEntry(100);
        std::cout<<"00000-pass"<<endl;

}

void TwoD_map(const char *file1 = "gmn_1M.root"){
	TFile *f = new TFile(file1);
	TTree *T = (TTree*)f->Get("T");
	//T->MakeClass("GEM");
	//GEM* G = new GEM;
	//T->Show(0);

	TCanvas *C1 = new TCanvas("c","Hitmap",1900,1000);
	TH2 *H1 = new TH2D("H1","Hit Map",100,-1.5,1.5,100,-1.5,1.5);
	
	Init(T);
	GEMHitTree gemhittree;

        gemhittree.fChain = T;
        gemhittree.fCurrent = -1;
        gemhittree.fChain->SetMakeClass(1);

        //Set branch addresses and branch pointers
        //std::cout<<"0-pass"<<endl;
        gemhittree.fChain->SetBranchAddress("Earm.BBGEM.hit.nhits",&gemhittree.Earm_BBGEM_hit_nhits,&gemhittree.b_Earm_BBGEM_hit_nhits);
        //std::cout<<"00-pass"<<endl;
        gemhittree.fChain->SetBranchAddress("Earm.BBGEM.hit.x",&gemhittree.Earm_BBGEM_hit_x,&gemhittree.b_Earm_BBGEM_hit_x);
        //std::cout<<"000-pass"<<endl;
        gemhittree.fChain->SetBranchAddress("Earm.BBGEM.hit.y",&gemhittree.Earm_BBGEM_hit_y,&gemhittree.b_Earm_BBGEM_hit_y);
        //std::cout<<"0000-pass"<<endl;
        //T->GetEntry(0);
        //std::cout<<"00000-pass"<<endl;
	
	int nevents = T -> GetEntries();
        std::cout<<"total events : "<<nevents<<endl;	

	for (int event = 0; event<nevents; ++event ){
		gemhittree.fChain->GetEntry(event);
		std::cout<<event<<endl;
		for (Int_t hit=0; hit<gemhittree.Earm_BBGEM_hit_nhits;hit++){
			std::cout<<"1-pass"<<endl; //  x: "<<gemhittree.Earm_BBGEM_hit_x[hit]<<" y:  "<<gemhittree.Earm_BBGEM_hit_y[hit]<<endl;
			//H1->Fill(gemhittree.Earm_BBGEM_hit_x[hit],gemhittree.Earm_BBGEM_hit_y[hit]);
		}
	}
	H1->Draw();
	C1->Draw();
	std::cout<<T->GetEntries()<<endl;
}

