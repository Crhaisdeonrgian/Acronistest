#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <graphics.h>
#include <conio.h>
using namespace std;

int k=0;


class CSVRow
{
    public:
        std::string const& operator[](std::size_t index) const
        {
            return m_data[index];
        }
        std::size_t size() const
        {
            return m_data.size();
        }
        void readNextRow(std::istream& str)
        {
            std::string         line;
            std::getline(str, line);

            std::stringstream   lineStream(line);
            std::string         cell;

            m_data.clear();
            while(std::getline(lineStream, cell, ','))
            {
                m_data.push_back(cell);
            }
            // This checks for a trailing comma with no data after it.
            if (!lineStream && cell.empty())
            {
                // If there was a trailing comma then add an empty element.
                m_data.push_back("");
            }
        }
    private:
        std::vector<std::string>    m_data;
};

std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}


long double sredznach(CSVRow head, CSVRow row){
    k++;
    vector<float>   quant;
    vector<int>   tlim;
    double sred=0;
    for (int i =2; i< row.size(); i++){
        if (k<2594){
            //cout<<"schas buit";
            //cout<<row[i];
            quant.push_back(stof(row[i]));
            //cout<<k<<endl;
        }
        else{
            quant.push_back(0);
        }
        tlim.push_back(stoi(head[i]));

    }
    sort(quant.begin(), quant.end());
    sort(tlim.begin(), tlim.end());

    vector<float>  quantrue;

    for (int i=1;i< quant.size();i++ ){
        quantrue.push_back(quant[i] - quant[i-1]);
    }
    float summ=0;
    for (int i=0; i<quantrue.size(); i++)
        summ+=quantrue[i]*tlim[i];
    if (row[1]!="")  {
        sred=summ / stoi(row[1]);
    }

    return sred;
}

double dispersion (double m, CSVRow head, CSVRow row){



    k++;
    vector<float>   quant;
    vector<int>   tlim;
    double disp=0;
    for (int i =2; i< row.size(); i++){
        if (k<2594){
            //cout<<"schas buit";
            //cout<<row[i];
            quant.push_back(stof(row[i]));
            //cout<<k<<endl;
        }
        else{
            quant.push_back(0);
        }
        tlim.push_back(stoi(head[i]));

    }
    sort(quant.begin(), quant.end());
    sort(tlim.begin(), tlim.end());

    vector<float>  quantrue;

    for (int i=1;i< quant.size();i++ ){
        quantrue.push_back(quant[i] - quant[i-1]);
    }
    float summ=0;
    for (int i=0; i<quantrue.size(); i++)
        summ+=quantrue[i]*(tlim[i] - m)*(tlim[i]-m);
    if (k<2594)  {
        disp=summ / (stoi(row[1])-1);
    }

    return disp;

}
int main()
{
    std::ifstream file("/Users/igorvozhga/acronis/ms_bucket.csv");
    CSVRow row;
    CSVRow t0;
    vector<time_t> x;
    vector<float>  y;
    vector<double>  y1;
    double sred=0;
    double disp=0;
    while(file >> row)
    {
        if (row[0] == "timestamp")
            t0=row;
        else{
            sred = sredznach(t0,row);
            disp = dispersion(sred, t0, row);
            x.push_back((time_t)stoi(row[0]));
            y.push_back(sred);
            y1.push_back(disp);
        }
    }
    /*vector<time_t>::iterator it = x.begin();
    int m = 0;
    while(it != x.end()) {
        m++;
        cout << "\n" << m << ")" << *it;
        it++;
    }*/



    x={1,2,3};
    y={1,2,3};
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");

    moveto(x[0],y[0]);
    for (int i=1; i<x.size(); i++){
        lineto(x[i], y[i]);

    }

