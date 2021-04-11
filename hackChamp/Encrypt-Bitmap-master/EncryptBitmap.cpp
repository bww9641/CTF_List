#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath> // for exponent
#include <cstdlib> // for making random numbers
#include <algorithm> // for sort

using namespace std;

//Structs Definement
struct imgInfo{
  long int Width;
  long int Height;
  long int Offset;
};
struct SquaresInfo{
    long int XFirstHome;
    long int YFirstHome;
    long int ColorForChange;
    long int Variance;
};

//Founctions Declaration
imgInfo GetImgInfo(string file_name);
vector<vector<vector<int> > > MakeImgVectorFromFile (string file_name);
vector<struct SquaresInfo> SeprateImgToSquares( vector<vector<vector<int> > > ImgVector
                            ,struct imgInfo ImgData);
int Average (vector<int> Numbers);
int Variance (vector <int> Numbers);
bool Structcompare(struct SquaresInfo lhs, struct SquaresInfo rhs);
vector<int> makeBinery (int Byte);
vector<vector<vector<int> > > CodingBitMap(vector<vector<vector<int> > > ImgVector,
                            vector <struct SquaresInfo> SquaresOfImg,string Text);
void SaveInNewBmp (string file_name ,vector<vector<vector<int> > > ImgVector);
void DecodingBitMap(vector<vector<vector<int> > > ImgVector,
                            vector <struct SquaresInfo> SquaresOfImg);
int makeByte(vector<int> Input);
vector<string> GetIputsAndChekingErors(void);
int ConvertStringToInt(string input);


int main()
{
  //first we get inputs and check erors
  vector<string> Order = GetIputsAndChekingErors();
  if(Order[0]!="e")
  {
    //we have a seed and set srand
    int seed = ConvertStringToInt(Order[2]);
    srand(seed);
    string file_name=Order[1];


    //first we get Image info with GetImgInfo founction:
    struct imgInfo IMG = GetImgInfo(file_name);

    /*Then we make a vector including pixels informations
          our vector have 3 diomensioal ! [Height][Width][Color: R=0 G=1 B=2]*/
      vector<vector<vector<int> > > ImgPixels;
      ImgPixels = MakeImgVectorFromFile(file_name);

    /*And we make a vector of structs that contains 8*8 squares sorted
      based on them Variance*/
      vector<struct SquaresInfo> SquaresOfImg = SeprateImgToSquares(ImgPixels,IMG);

    if(Order[0]=="a")
    {
      string Text=Order[3];
    /*And finally we code the img vecotor by squares and random numbers
      that we'll create*/
      ImgPixels = CodingBitMap(ImgPixels, SquaresOfImg,Text);
    /*And at the end make new bitmap file*/
      SaveInNewBmp(file_name,ImgPixels);
    }
    if(Order[0]=="b")
    {
      /*And finally we decode the img vector and print it*/
      DecodingBitMap(ImgPixels,SquaresOfImg);
    }
  }
}

imgInfo GetImgInfo(string file_name){

  // The file... We open it with it's constructor
    imgInfo ReturnStruct ;
    std::ifstream file(file_name.c_str(), std::ios::binary);
    if(!file)
    {
      std::cout << "Failure to open bitmap file.\n";
      return ReturnStruct;
    }


    //Some vector for including bytes
    vector<int> WidthBytes;
    vector<int> HeightBytes;
    vector<int> PixelsOffset;


    for(int i=0;i<54;i++)
    {
      int temp = file.get();
      //Get Pixels Offset bytes
      if(i>=10 && i<=13)
      {
        PixelsOffset.push_back(temp);
      } else if (i==14)
      {
        // make a long int for pixel offset
        ReturnStruct.Offset=pow(2,24)*PixelsOffset[3]
          + pow(2,16)*PixelsOffset[2] + pow(2,8)*PixelsOffset[1] + PixelsOffset[0] ;
      }

      //Get width Bytes
      if(i>= 18 && i <= 21)
      {
        WidthBytes.push_back(temp);
      } else if (i==22)
      {
        // make a long int with width bytes
        ReturnStruct.Width=pow(2,24)*WidthBytes[3]
          + pow(2,16)*WidthBytes[2] + pow(2,8)*WidthBytes[1] + WidthBytes[0] ;
      }

      //Get HeightBytes
      if(i>= 22 && i <= 25)
      {
        HeightBytes.push_back(temp);
      }else if (i==26){
        ReturnStruct.Height=pow(2,24)*HeightBytes[3]
          + pow(2,16)*HeightBytes[2] + pow(2,8)*HeightBytes[1] + HeightBytes[0] ;

      }
    }
      return ReturnStruct;
}


vector<vector<vector<int> > > MakeImgVectorFromFile (string file_name){
  //first we get img data
    struct imgInfo ImgData = GetImgInfo(file_name);
    // make return vector
    vector <vector<vector<int> > > ReturnVector;
    // The file... We open it with it's constructor
      imgInfo ReturnStruct ;
      std::ifstream file(file_name.c_str(), std::ios::binary);
      if(!file)
      {
        std::cout << "Failure to open bitmap file.\n";
        return ReturnVector;
      }
      for (int i=0 ; i < ImgData.Offset ; i++)
      {
        file.get();

    }
    // End of each width is some 0 bytes (because width isnt multiple of 4)
        // so we should get them but dont store them
    int extraGet ;
    extraGet=((ImgData.Width*3)%4);
    if (extraGet!=0)
    {
        extraGet= 4 - extraGet;
    }

    for(int i=0 ; i<ImgData.Height; i++)
    {

        vector<vector <int> > Row;
        for(int j =0 ; j<ImgData.Width; j++)
        {
            vector<int> Colors(3);
            Colors[2] = file.get();
            Colors[1] = file.get();
            Colors[0]= file.get();
            Row.push_back(Colors);
         }
        for(int j=0 ; j<extraGet ; j++)
        {
            file.get();
        }
        ReturnVector.push_back(Row);
      }
      return ReturnVector;

}

vector<struct SquaresInfo> SeprateImgToSquares( vector<vector<vector<int> > > ImgVector
                                          ,struct imgInfo ImgData)
{

    vector<struct SquaresInfo> Squares;

    // here we fill structs with 8*8 squares data


    for( int i=0 ; i<(ImgData.Height)-(ImgData.Height%8); i=i+8)
    {

        for(int j=0 ; j<(ImgData.Width)-(ImgData.Width%8); j=j+8)
        {
            struct SquaresInfo tempSquareStruct;
            tempSquareStruct.XFirstHome=i;
            tempSquareStruct.YFirstHome=j;
            // we should select one color for change
            tempSquareStruct.ColorForChange=rand()%3;
            //And calculate the variance of that square
            vector<int> Numbers;
            for(int k=0; k<8 ; k++ )
            {
                for(int m=0; m<8; m++)
                {
                    Numbers.push_back(ImgVector[k+i][m+j][tempSquareStruct.ColorForChange]);
                }
            }
            tempSquareStruct.Variance = Variance(Numbers);
            Squares.push_back(tempSquareStruct);

        }
    }
    // and finally we sort it base on varinace
    sort(Squares.begin(),Squares.end(),Structcompare);

    return Squares;
}
int Variance (vector<int> Numbers)
{
  //we change the LSB to zero first
  for(int i =0 ; i<64;i++ )
  {
    Numbers[i]=Numbers[i]-(Numbers[i]%2);
  }
    int Avg= Average(Numbers);
    int temp=0;
    for(int i=0;i<64;i++)
    {
        Numbers[i]=pow((Numbers[i]-Avg),2);
    }
    for(int i =0; i<64;i++)
    {
        temp+= Numbers[i];
    }
    return temp/64;
}
int Average (vector<int> Numbers)
{
    int temp=0;
    for(int i =0; i<64;i++)
    {
        temp+= Numbers[i];
    }
    return temp/64;
}
// this founction is for sort
bool Structcompare(struct SquaresInfo lhs, struct SquaresInfo rhs)
{ return lhs.Variance > rhs.Variance; }
// With this founc we make binery numbers from Bytes
vector<int> makeBinery (int Byte)
{
  vector<int> Num(8);
  for(int i=7;i>0;i--)
  {
    Num[i]=Byte%2;
    Byte /= 2;
  }
  Num[0]=Byte;
  return Num;
}

vector<vector<vector<int> > > CodingBitMap(vector<vector<vector<int> > >
      ImgVector,vector <struct SquaresInfo> SquaresOfImg,string Text)
{
  Text.push_back('\n');

  int StrLength = Text.length();
  for(int i=0;i<StrLength;i++)
  {
    // we make a random number and choose the correct block for change
    vector<int> reservedBlocks;
    for(int j=0;j<8;j++)
    {
      int randomNum1=rand()%8;
      int randomNum2=rand()%8;
      int Flag=0;
      for(int k =0 ; k < reservedBlocks.size();k++)
      {
        if(reservedBlocks[k]==(randomNum1*10)+randomNum2)
        {
          Flag=1;
        }
      }
      if (Flag==1)
      {
        j--;
        Flag=0;
        continue;
      }
      else {
        reservedBlocks.push_back((randomNum1*10)+randomNum2);
      }
    }
    int tempValue=0;
    vector<int> tempVector;
    // here we create a binery number from ASCII code of every character
    tempValue=(int)Text[i];
    tempVector=makeBinery(tempValue);
    for(int j=0 ; j<8; j++)
    {
      // we change LSB of random block

      int Random1=reservedBlocks[j]/10 + SquaresOfImg[i].XFirstHome ;
      int Random2=reservedBlocks[j]%10 + SquaresOfImg[i].YFirstHome;
        ImgVector[Random1][Random2][SquaresOfImg[i].ColorForChange] =
        (ImgVector[Random1][Random2][SquaresOfImg[i].ColorForChange])-
        (ImgVector[Random1][Random2][SquaresOfImg[i].ColorForChange]%2)
          + tempVector[j];

    }

  }
return ImgVector;
}
void SaveInNewBmp (string file_name ,vector<vector<vector<int> > > ImgVector)
{
  // Here we creat new file and put pixels into that
  //first we get img data
    struct imgInfo ImgData = GetImgInfo(file_name);
    // The file... We open it with it's constructor
      imgInfo ReturnStruct ;
      std::ifstream fileIn(file_name.c_str(), std::ios::binary);
      if(!fileIn)
      {
        std::cout << "Failure to open bitmap file.\n";
      }
      std::ofstream fileOut("output.bmp", std::ios::binary);
      for (int i=0 ; i < ImgData.Offset ; i++)
      {
        int temp=fileIn.get();
        fileOut.put(temp);
      }
    // End of each width is some 0 bytes (because width isnt multiple of 4)
        // so we should get them but dont store them
    int extraGet ;
    extraGet=((ImgData.Width*3)%4);
    if (extraGet!=0)
    {
        extraGet= 4 - extraGet;
    }

    for(int i=0 ; i<ImgData.Height; i++)
    {
        for(int j =0 ; j<ImgData.Width; j++)
        {

            fileOut.put(ImgVector[i][j][2]);
            fileOut.put(ImgVector[i][j][1]);
            fileOut.put(ImgVector[i][j][0]);

         }
        for(int j=0 ; j<extraGet ; j++)
        {
            fileOut.put(0);
        }

      }

}
void DecodingBitMap(vector<vector<vector<int> > > ImgVector,
                            vector <struct SquaresInfo> SquaresOfImg)
{
  int i=0;
  char GetedChar=0;
  string OutPut="";
  while(GetedChar!='\n')
  {
    // we make a random number and choose the correct block for geting character
    vector<int> reservedBlocks;
    for(int j=0;j<8;j++)
    {
      int randomNum1=rand()%8;
      int randomNum2=rand()%8;
      int Flag=0;
      for(int k =0 ; k < reservedBlocks.size();k++)
      {
        if(reservedBlocks[k]==(randomNum1*10)+randomNum2)
        {
          Flag=1;
        }
      }
      if (Flag==1)
      {
        j--;
        Flag=0;
        continue;
      }
      else {
        reservedBlocks.push_back((randomNum1*10)+randomNum2);
      }
    }
    int tempValue=0;
    vector<int> tempVector(8);
    // here we create a binery number from ASCII code of every character
    for(int j=0 ; j<8; j++)
    {

      // we get LSB and make a vector in binary
      int Random1=reservedBlocks[j]/10 + SquaresOfImg[i].XFirstHome ;
      int Random2=reservedBlocks[j]%10 + SquaresOfImg[i].YFirstHome;
      tempVector[j]=ImgVector[Random1][Random2][SquaresOfImg[i].ColorForChange]%2;

    }

    tempValue=makeByte(tempVector);
    GetedChar=(char) tempValue ;

    OutPut.push_back(GetedChar);
    i++;
  }
  cout<<OutPut;
}
int makeByte(vector<int> Input){
  int temp=0;
  for(int i =7 ; i>=0 ; i--)
  {
    temp += (Input[i]*pow(2,7-i));
  }
  return temp;
}

vector<string> GetIputsAndChekingErors(void){
  string Order = "";
  vector<string> ReturnOrder;
  // How to get a string/sentence with spaces
//first we get order (encrypt or decrypt)
  getline(cin, Order);
  if(Order=="encrypt")
  {
    ReturnOrder.push_back("a");
  } else if(Order=="decrypt")
  {
    ReturnOrder.push_back("b");
  } else{
    cout<<"Unknown Order!Try again"<<endl;
      ReturnOrder.push_back("e");
    return ReturnOrder;
  }
  //then we get file name
  string file_name="";
  getline(cin,file_name);
  ReturnOrder.push_back(file_name);
  std::ifstream file(file_name.c_str(), std::ios::binary);
  if(!file)
  {
    std::cout << "Failure to open bitmap file.\n";
    ReturnOrder[0]="e";
      return ReturnOrder;
  }

  string seed="";
  getline(cin,seed);
  ReturnOrder.push_back(seed);
  int myStream = ConvertStringToInt(seed);
  if(myStream>=1000000 || myStream<1000 )
  {
    ReturnOrder[0]="e";
    cout<<"Invalid seed!Please try again"<<endl;
    return ReturnOrder;
  }
  if(ReturnOrder[0]=="a")
  {
      string Text="";
      getline(cin,Text);
      struct imgInfo IMG=GetImgInfo(file_name);
      if((Text.length() +1) >= ((IMG.Width * IMG.Height)/64) )
      {
        cout<<"Your text is too long to coding"<<endl;
        ReturnOrder[0]="e";
        return ReturnOrder;
      }
      ReturnOrder.push_back(Text);
    }

return ReturnOrder;
}

int ConvertStringToInt(string input){
  int length = input.length();
  int OutPut=0;
  for(int i=0 ; i<length ; i++)
  {
    int temp =(int)(input[i]-48);
    OutPut += temp*(pow(10,length-i-1));
  }
  return OutPut;
}
