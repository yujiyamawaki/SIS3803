TString safeName(TString name)
{
    TObject* old = gROOT->FindObject(name);
    if(old) delete old;
    return name;
}

void GaussFit(int runnum)
{
    Int_t rebin=1, bin0=0, binmax=20000,tmp;
    Double_t x, sec,time, mean=0, sigmaT=0, sigmaX=0, fuga=0;
    Char_t comma;

    TH1D *h1 = new TH1D(safeName("h1"),Form("Beam Intensity Distribution #%04d",runnum),(binmax - bin0)/rebin,bin0,binmax);
    ifstream fin(Form("../../data/scadata%04d.csv",runnum));
    if(!fin){
        cout << "ifs open error" << endl;
        exit(1);
    }
    //while(fin >> time >> comma >> tmp >> comma >> tmp >> comma >> tmp >> comma >> x >> comma >> tmp >> comma >> tmp >> comma >> tmp >> comma
    while(fin >> time >> comma >> sec >> comma >> tmp >> comma >> tmp >> comma >> tmp >> comma >> x >> comma >> tmp >> comma >> tmp >> comma >> tmp >> comma
            >> tmp >> comma >> tmp >> comma >> tmp >> comma >> tmp >> comma >> tmp >> comma >> tmp >> comma >> tmp >> comma >> tmp >> comma >> tmp){
        if(bin0<=x && x<=binmax)h1->Fill(x);
    }
    fin.close();

    h1->Fit("gaus","","",bin0,binmax);
    h1->SetLineColor(kBlue);
    h1->GetXaxis()->SetLabelSize(0.04);
    h1->GetYaxis()->SetLabelSize(0.04);
    h1->GetXaxis()->SetTitleSize(0.04);
    h1->GetYaxis()->SetTitleSize(0.04);
    h1->GetXaxis()->SetTitle("Counts/100ms");
    h1->GetYaxis()->SetTitle("Frequency");
    h1->Draw();

    mean = h1->GetMean();
    sigmaT = h1->GetStdDev();
    fuga = sigmaT*sigmaT-mean;
    if(fuga > 0)sigmaX = sqrt(fuga);

    ofstream ofs(Form("MeanVsStdDev.csv",runnum),ios_base::app);
    if(!ofs){
        cout << " ofs file open error" << endl;
        exit(1);
    }
    ofs << runnum << "," << mean << "," << sigmaT << "," << sigmaX << endl;
    ofs.close();

}

