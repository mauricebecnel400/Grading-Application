// Assignment : Project 1
// File : becnelP1.cpp
// Date : September 24th 2016
// Description: This program creates 4 reports from an input file 'grades.txt' The first report containing
// all the grade types. The second contains only homework and labs, the third report contains projects and 
// the final report prints outs the test and quizzes. At the end of each report the program calculates 
// a grade precentage and grade letter. The program also prints out a total weighted grade precentage and
// total weighted letter grade.
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

// The definition for the Grade Class.
class Grade
{
  public:
    Grade ();
    Grade (const Grade & OtherGrade);
    void SetGType (char gt);
    void SetDate (string dt);
    void SetScore (int scr);
    void SetPossible (int poss);
    void SetLetterGrade ();
    void SetTitle (string ttl);
    char GetGType () const;
    string GetDate () const;
    int GetScore () const;
    int GetPossible () const;
    char GetLetterGrade () const;
    string GetTitle () const;
    void WriteGradeData (ostream & output) const;
  private:
    char gtype;
    string date;
    int score;
    int possible;
    char letter;
    string title;
};

// MAXGRADES contain the maxium number of grades
const int MAXGRADES = 100;

// Prototypes for funtions used by this program
int ReadFile (Grade GradeArray [] );
float WriteReport (ostream & output, const string  title, Grade GradeArray [],
int first, int last);
void Sort (Grade GradeArray [], int N);
void Swap (Grade & a, Grade & b);
int Num_HL (Grade GradeArray [], int start, int count);
int Num_P (Grade GradeArray [], int start, int count);
int Num_QT (Grade GradeArray [], int start, int count);
string Final_Letter_Grade (float percent);

int main ()
{
  // Declare an array of gradesarray object and the call of the ReadFile 
  Grade GradeArray [MAXGRADES];
  int count = ReadFile (GradeArray);

  // Calls WriteReport function for All Grades Report and then calls the Sort funtion.
  WriteReport (cout, "All Grades ", GradeArray, 0, count);
  Sort (GradeArray, count);
  
  // Calling of the rest of Write Report Funtions, and the boundaries of each Write Report
  int numberHL = Num_HL(GradeArray, 0, count);
  float totalHL_percent = WriteReport (cout, "Homework and Labs ", GradeArray, 0, numberHL);
  int numberP = numberHL + Num_P (GradeArray, numberHL, count);
  float totalP_percent = WriteReport (cout, "Projects ", GradeArray, numberHL, numberP);
  int numberTQ = numberP + Num_QT(GradeArray, numberP, count);
  float totalQT_percent = WriteReport (cout, "Quizzes and Tests ", GradeArray, numberP, numberTQ);

  // Summation of the all the percents from the Write Report Functions. Also includes the wieghted
  // perentage of each category. Then calls the Final Letter Grade function.
  float totalgrade_percent = (totalHL_percent * .2) + (totalP_percent * .3) + (totalQT_percent * .5);
  string lettergrade = Final_Letter_Grade (totalgrade_percent);
  
  // Prints out the the overall percentage and letter grade.
  cout << setw (5) << right << "Overall Percentage: " << fixed << setprecision(1)
   << totalgrade_percent << "%" << "\tGrade: " << lettergrade << endl;
}

// This function calculates the letter grade using the parameter percent which is the final
// weighted percentage.
string Final_Letter_Grade (float percent)
{
  if (percent > 93)
  {
    return "A";
  }
  else if ((percent < 93) && (percent >= 90))
  {
    return "A-";
  }
  else if ((percent < 90) && (percent >= 87))
  {
    return "B+";
  }
  else if ((percent < 87) && (percent >= 83))
  {
    return "B";
  }
  else if ((percent < 83) && (percent >= 80))
  {
    return "B-";
  }
  else if ((percent < 80) && (percent >= 77))
  {
    return "C+";
  }
  else if ((percent < 77) && (percent >= 73))
  {
    return "C";
  }
  else if ((percent < 73) && (percent >= 70))
  {
    return "C-";
  }
  else if ((percent < 70) && (percent >= 67))
  {
    return "D+";
  }
  else if ((percent < 67) && (percent >= 63))
  {
    return "D";
  }
  else if ((percent < 63) && (percent >= 60))
  {
    return "D-";
  }
  else
  {
    return "F";
  }
}

// Iterates through the grades array and looks for homework and labs grade type and increments
// a total and then returns that total.
int Num_HL (Grade GradeArray [], int start, int count)
{
  int total_HL = 0;
  for (int i = 0; i < count; i++)
  {
    if ((GradeArray[i].GetGType() == 'H') || (GradeArray[i].GetGType() == 'L'))
    {
      total_HL++;
    }
  }
  return total_HL;
}

// Iterates through the grades array and looks for projects grade type and increments
// a total and then returns that total.
int Num_P (Grade GradeArray [], int start, int count)
{
  int total_P = 0;
  for (int i = 0; i < count; i++)
  {
    if (GradeArray[i].GetGType() == 'P')
    {
      total_P++;
    }
  }
  return total_P;
}

// Iterates through the grades array and looks for quizzes and exams grade type and increments
// a total and then returns that total.
int Num_QT (Grade GradeArray [], int start, int count)
{
  int total_QT = 0;
  for (int i = 0; i < count; i++)
  {
    if ((GradeArray[i].GetGType() == 'Q')|| (GradeArray[i].GetGType() == 'T'))
    {
      total_QT++;
    }
  }
  return total_QT;
}

// Checks input file and then reads file and counts the words. Then returns count.
int ReadFile (Grade GradeArray [] )
{
  ifstream input ("grades.txt");
  if (input.fail())
  {
    cout << "" << endl;
    exit(2);
  }
  char gtype;
  string date;
  int score;
  int possible;
  char letter;
  string title;
  int count = 0;
  string oneword;
  string rest;
  float grade_percent;
  // Reads and count the words in the file
  while (input >> gtype >> date >> score >> possible >> title)
  {
    getline(input, rest);
    title+= rest;
    GradeArray[count].SetGType(gtype);
    GradeArray[count].SetDate(date);
    GradeArray[count].SetScore(score);
    GradeArray[count].SetPossible(possible);
    GradeArray[count].SetLetterGrade();
    GradeArray[count].SetTitle(title);
    count++;
  }
  return count;
}

// This function ouputs the report, and returns a total percentage in each report.
float WriteReport (ostream & output, string title, Grade GradeArray [], int first, int last)
{
  output << title << "Report\n";
  output << setw (5) << left << "Type";
  output << setw (5) << right << "Date";
  output << setw (10) << "Score";
  output << setw (10) << "Possible";
  output << setw (8) << "Grade";
  output << setw (3) <<  "";
  output << setw (40) << left << "Title" << endl;

  float totalscore = 0;
  float totalpossible = 0;

// Iterates through the array and calls the Write Grade Data function also increaments
// totalscore and total possible so we can calculate the total percent.
  for (int i = first; i < last; i++)
  {
    GradeArray[i].WriteGradeData(output);
    totalscore += GradeArray[i].GetScore();
    totalpossible += GradeArray[i].GetPossible();
  }
  output << setw (20) << right << "---";
  output << setw (10) << "---" << endl;
  output << setw (20) << right << totalscore;
  output << setw (10) << totalpossible << endl;
  float total_percent = (totalscore / totalpossible) * 100;

  output << setw (5) << left << title << "Percentage: " << fixed << setprecision(1) << total_percent << "%" << endl;
  output << setprecision(0) << endl;
  return total_percent;

}

// Outputs the Data for the Write Report function.
void Grade::WriteGradeData (ostream & output) const
{
  output << setw (5) << left << gtype;
  output << setw (5) << right << date;
  output << setw (10) << score;
  output << setw (10) << possible;
  output << setw (8) << letter;
  output << setw (3) << "";
  output << setw (40) << left << title << endl;
}

// Sorts Grade array first based off of grade type and if those are equal then
// it sorts based on grade date.
void Sort (Grade GradeArray [], int N)
{
  int i = 1;
  while (i < N)
  {
    int j = i;
    while ((j > 0) && (GradeArray[j].GetGType() < GradeArray[j-1].GetGType()
    || GradeArray[j].GetGType() == GradeArray[j-1].GetGType()))
    {
      if (GradeArray[j].GetGType() < GradeArray[j-1].GetGType())
      {
        Swap( GradeArray[j], GradeArray[j-1]);
      }
      else if (GradeArray[j].GetGType() == GradeArray[j-1].GetGType())
      {
        if (GradeArray[j].GetDate() < GradeArray[j-1].GetDate())
        {
          Swap (GradeArray[j], GradeArray[j-1]);
        }
      }
      j--;
    }
    i++;
  }
}

void Swap (Grade & a, Grade & b)
{
  Grade temp;
  temp = a;
  a = b;
  b = temp;
}

Grade::Grade()
{
  gtype = ' ';
  date = " ";
  score = 0;
  possible = 0;
  letter = ' ';
  title = " ";

}

// Sets Grade type in the funtion.
void Grade::SetGType (char gt)
{
	gtype = gt;
}

// Calculates the grade percent and sets letter grade for each report.
void Grade::SetLetterGrade ()
{
  float grade_percent = ((float) score / (float) possible)*100;
  if (grade_percent >= 90)
  {
    letter = 'A';
  }
  else if (grade_percent >= 80)
  {
    letter = 'B';
  }
  else if (grade_percent >= 70)
  {
    letter = 'C';
  }
  else if (grade_percent >= 60)
  {
    letter = 'D';
  }
  else if (grade_percent < 60)
  {
    letter = 'F';
  }
}

// Construtor 
Grade::Grade (const Grade & OtherGrade)
{
  gtype = OtherGrade.gtype;
  date = OtherGrade.date;
  score = OtherGrade.score;
  possible = OtherGrade.possible;
  letter = OtherGrade.letter;
  title = OtherGrade.title;
}

// Sets Grade Date.
void Grade::SetDate (string d)
{
	date = d;
}

// Sets Score.
void Grade::SetScore (int scr)
{
	score = scr;
}

// Sets Possible
void Grade::SetPossible (int poss)
{
	possible = poss;
}

// Sets assignment title.
void Grade::SetTitle (string ttl)
{
	title = ttl;
}

// Returns grade type.
char Grade::GetGType () const
{
	return gtype;
}

// Returns date.
string Grade::GetDate () const
{
	return date;
}

// Returns score.
int Grade::GetScore () const
{
	return score;
}

// Returns possible.
int Grade::GetPossible () const
{
	return possible;
}

// Returns Letter Grade.
char Grade::GetLetterGrade () const
{
  return letter;
}
