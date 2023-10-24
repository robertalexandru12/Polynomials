#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <complex>

using namespace std;

class Polynomial{
protected:
    vector<double> mCoeffs;
    uint32_t mDegree;
public:
    Polynomial(const vector<double> &coef){
        mCoeffs=coef;
        mDegree=mCoeffs.size()-1;
    }
    Polynomial(uint32_t val){
        mDegree=val;
        for(int i=0;i<=val;i++){
            mCoeffs.push_back(0);
        }
    }
    virtual std::vector<std::complex<double>> roots() const {
        cout<<"Implementation for method roots for polynomials with degree = "<<mDegree<<" is not available.\n";
        vector<complex<double>> x;
        return x;
    }
    double calculate(double value) const{
        double rez=0;
        for(int i = 0;i<mCoeffs.size();i++){
            rez=rez+mCoeffs[i]*pow(value,(mCoeffs.size()-1-i));
        }
        return rez;
    }
    std::complex<double> calculate(const std::complex<double>& value) const
    {
        complex<double> rezultat;
        return rezultat;
    }

    uint32_t getDegree() const{
        return mDegree;
    }
    double operator[](uint32_t index) const{
        return mCoeffs[index];
    }
    double& operator[](uint32_t index){
        return mCoeffs[index];
    }
    vector<double> getVector() const{
        return mCoeffs;
    }
    Polynomial derivate() const {
        uint16_t grad;
        if(mDegree==0){
            Polynomial pol(0);
            return pol;
        }
        else{
            Polynomial pol(mDegree-1);
        for (int i = 0; i <pol.mCoeffs.size(); i++) {
            pol.mCoeffs[i] = mCoeffs[i] * (mDegree - i);
        }
        return pol;
    }
    }
    Polynomial operator+(const Polynomial& rhs) const{
        if(rhs.getDegree()>mDegree){
            Polynomial pol(rhs.mCoeffs.size()-1);
            for(int i=0;i<rhs.mCoeffs.size();i++){
                pol.mCoeffs[i]=rhs.mCoeffs[i];
            }
            cout<<endl;
            int k=0;
            for(int i = mCoeffs.size()-1;i>=0;i--){
                pol.mCoeffs[pol.mCoeffs.size()-1-k]+=mCoeffs[i];
                k++;
            }
            return pol;
        }
        else
        {
            Polynomial pol(mCoeffs.size()-1);
            for(int i=0;i<mCoeffs.size();i++){
                pol.mCoeffs[i]=mCoeffs[i];
            }
            int k=0;
            for(int i = rhs.mCoeffs.size()-1;i>=0;i--){
                pol.mCoeffs[pol.mCoeffs.size()-1-k]+=rhs.mCoeffs[i];
                k++;
            }
            return pol;
        }
    }
    Polynomial operator*(const Polynomial& rhs) const
    {
        Polynomial pol(rhs.mDegree+mDegree);
        for(int i=0;i<mCoeffs.size();i++){
            int grade_i = mCoeffs.size()-1-i;
            for(int j=0;j<rhs.mCoeffs.size();j++){
                int grade_j = rhs.mCoeffs.size()-1-j;
                pol.mCoeffs[pol.mCoeffs.size()-(grade_i+grade_j)-1]+= mCoeffs[i]*rhs.mCoeffs[j];
            }
        }
        return pol;
    }
    Polynomial& operator*=(const double constant){
        for(int i=0;i<mCoeffs.size();i++){
            mCoeffs[i]*=constant;
        }
        return *this;
    }
    Polynomial& operator/=(const double constant){
        for(int i=0;i<mCoeffs.size();i++){
            mCoeffs[i]/=constant;
        }
        return *this;
    }
    void print(){
        int k=0;
        for(double x : mCoeffs){
            if(k==0){
                cout<<fixed<<setprecision(3)<<x<<"*x^"<<mCoeffs.size()-k-1;
            }
            else{
                if(x<0) cout<<fixed<<setprecision(3)<<x<<"*x^"<<mCoeffs.size()-k-1;
                else cout<<"+"<<fixed<<setprecision(3)<<x<<"*x^"<<mCoeffs.size()-k-1;
            }
            k++;
        }
        cout<<endl;
    }

};
class ZeroDegreePolynomial:public Polynomial{
public:
    ZeroDegreePolynomial(const vector<double> &x) : Polynomial(x) {

    }
    std::vector<std::complex<double>> roots() const{
        vector<complex<double>> v;
        cout<<"Polynomials with degree 0 doesn't have roots.\n";
        return v;
    }
};
class FirstDegreePolynomial:public Polynomial{
public:
    FirstDegreePolynomial(const vector<double> &x) : Polynomial(x) {

    }
    std::vector<std::complex<double>> roots() const{
        vector<complex<double>> v;
        double eq=0;
        eq-=mCoeffs[1];
        double rez=eq/mCoeffs[0];
        complex<double> solutie(rez,0);
        v.push_back(solutie);
        return v;
    }
};
class SecondDegreePolynomial:public Polynomial{
public:
    SecondDegreePolynomial(const vector<double> &x) : Polynomial(x) {

    }
    std::vector<std::complex<double>> roots() const{
        vector<complex<double>> v;
        double delta = pow(mCoeffs[1],2)-4*mCoeffs[0]*mCoeffs[2];
        if(delta>0){
            double x1,x2;
            x1=((-1)*mCoeffs[1]+ sqrt(delta))/2*mCoeffs[0];
            x2=((-1)*mCoeffs[1]- sqrt(delta))/2*mCoeffs[0];
            complex<double> sol1(x1,0);
            complex<double> sol2(x2,0);
            v.push_back(sol1);
            v.push_back(sol2);
        }
        if(delta==0){
            double x1;
            x1=((-1)*mCoeffs[1]+ sqrt(delta))/2*mCoeffs[0];
            complex<double> sol1(x1,0);
            v.push_back(sol1);
        }
        if(delta<0){
            double real = (-1)*mCoeffs[1]/2*mCoeffs[0];
            double img = sqrt(abs(delta))/2*mCoeffs[0];
            complex<double> sol1(real,img);
            complex<double> sol2(real,(-1)*img);
            v.push_back(sol1);
            v.push_back(sol2);
        }
        return v;
    }
};


int main(){
    vector<Polynomial> polinoame;
    int n;
    char s[100];
    cin>>n;
    cin.get();
    for(int i=0;i<n;i++){
        cin.getline(s,100);
        vector<double> coef;
        char * p = strtok(s," ");
        while(p!=NULL){
            double x = stoi(p);
            if(x!=0) coef.push_back(x);
            p= strtok(NULL," ");
        }
        Polynomial pol(coef);
        polinoame.push_back(pol);
    }
    string comanda;
    while(cin>>comanda){
        if(comanda=="roots"){
            int index;
            cin>>index;
            if(polinoame[index].getDegree()==0){
                cout<<"Polynomials with degree 0 doesn't have roots.\n"<<endl;
                ZeroDegreePolynomial pol(polinoame[index].getVector());
                vector<complex<double>> sol = pol.roots();
            }
            if(polinoame[index].getDegree()==1){
                FirstDegreePolynomial pol(polinoame[index].getVector());
                vector<complex<double>> sol = pol.roots();
                cout<<"Roots of polynomial with index "<<index<<" are:"<<endl;
                cout<<"x1 = "<<fixed<<setprecision(3)<<sol[0].real()<<" ";
                cout<<endl;
            }
            if(polinoame[index].getDegree()==2){
                SecondDegreePolynomial pol(polinoame[index].getVector());
                vector<complex<double>> sol = pol.roots();
                cout<<"Roots of polynomial with index "<<index<<" are:"<<endl;
                for(int i=0;i<sol.size();i++){
                    if(sol[i].imag()==0){
                        cout<<"x"<<i+1<<" = " <<fixed<<setprecision(3)<<sol[0].real()<<" ";
                        cout<<endl;
                    }
                    else{
                        cout<<"x"<<i+1<<" = " <<fixed<<setprecision(3)<<sol[0].real();
                        if(sol[i].imag()<0){
                            cout<<fixed<<setprecision(3)<<sol[i].imag()<<"*i";
                        }
                        else cout<<"+"<<fixed<<setprecision(3)<<sol[i].imag()<<"*i";
                    }
                    cout<<endl;
                }
            }
            if(polinoame[index].getDegree()>2)
                cout<<"Implementation for method roots for polynomials with degree = "<<polinoame[index].getDegree()<<" is not available.\n";

        }
        if(comanda=="derivate"){
            int index1,index2;
            cin>>index1>>index2;
            Polynomial pol = polinoame[index2].derivate();
            polinoame[index1]=pol;
        }
        if(comanda=="div"){
            int index1;
            double val;
            cin>>index1>>val;
            polinoame[index1]= polinoame[index1].operator/=(val);
        }
        if(comanda=="mult"){
            int k=0;
            double v1,v2,v3;
            cin.getline(s,100);
            char * p = strtok(s," ");
            while(p!=NULL){
                k++;
                if(k==1) v1=stoi(p);
                if(k==2) v2=stoi(p);
                if(k==3) v3=stoi(p);
                p= strtok(NULL," ");

            }
            if(k==2){
                int index=v1;
                double val=v2;
                polinoame[index] = polinoame[index].operator*=(val);

            }
            if(k==3){
                int i=v1,j=v2,k=v3;
                Polynomial pol = polinoame[j].operator*(polinoame[k]);
                polinoame[i]=pol;
            }
        }
        if(comanda=="add"){
            int i,j,k;
            cin>>i>>j>>k;
            Polynomial pol = polinoame[j].operator+(polinoame[k]);

            polinoame[i]=pol;

        }
    }
    for(Polynomial x : polinoame){
       x.print();
    }
    return 0;
}
