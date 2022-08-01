#include "stdafx.h"
#include <iostream>

using namespace std;

class OverflowException {
   public:
      OverflowException() {
         cout << endl << "Exception created!" << endl;
      }
      OverflowException(const OverflowException&) {
         cout << "Exception copied!" << endl;
      }
      ~OverflowException() {
         cout << "Exception finished!" << endl;
      }
};

template <class T1, class T2>
class CoordPoint {
   protected:
      T1 X;
      T2 Y;
   public:
      CoordPoint();
      CoordPoint(T1, T2);
      virtual ~CoordPoint() {
         cout << "Message from the \"CoordPoint\" - destroyed!" << endl;
      }
      T1 GetX() const {
         return X;
      }
      void SetX(T1 X) {
         this->X = X;
      }
      T2 GetY() const;
      void SetY(T2);
      virtual void Print() const;
};

template <class T1, class T2>
class DisplayPoint : public CoordPoint<T1, T2> {
   private:
      unsigned int Color;
   public:
      DisplayPoint():CoordPoint<T1, T2>(), Color(0) {
      }
      DisplayPoint(T1, T2, unsigned int);
      virtual ~DisplayPoint() {
         cout << endl << "Message from the \"DisplayPoint\" - destroyed!" << endl;
      }
      unsigned int GetColor() const {
         return Color;
      }
      void SetColor(unsigned int PColor) {
         this->Color = PColor;
      }
      virtual void Print() const;
};

template <class T1, class T2>
class DisplayBrokenLine {
   private:
      typedef DisplayPoint<T1, T2>* DPPointer;
      DPPointer *Nodes;

      static const unsigned int DEF_MAX_SIZE;
      unsigned int MaxSize;
      unsigned int Length;
      unsigned int LineColor;

   public:
      DisplayBrokenLine():MaxSize(DEF_MAX_SIZE), Length(0), LineColor(0) {
         Nodes = new DPPointer[MaxSize];
      }
      DisplayBrokenLine(unsigned int MaxSize, unsigned int LineColor) : MaxSize(MaxSize), Length(0) {
         this->LineColor = LineColor;
         Nodes = new DPPointer[MaxSize];
      }
      ~DisplayBrokenLine();
      static unsigned int GetDefaultMaxSize() {
         return DEF_MAX_SIZE;
      }
      int GetMaxSize() const {
         return MaxSize;
      }
      int GetLength() const{
         return Length;
      }
      void AddNode(const DisplayPoint<T1, T2>&);
      void Print() const;
};

template <class T1, class T2>
const unsigned int DisplayBrokenLine<T1, T2>::DEF_MAX_SIZE = 5;

template <class T1, class T2>
CoordPoint<T1, T2>::CoordPoint() : X(0), Y(0) {
}

template <class T1, class T2>
CoordPoint<T1, T2>::CoordPoint(T1 Px, T2 Py) : X(Px) {
   Y = Py;
}

template <class T1, class T2>
inline T2 CoordPoint<T1, T2>::GetY() const {
   return Y;
}

template <class T1, class T2>
inline void CoordPoint<T1, T2>::SetY(T2 Y) {
   this->Y = Y;
}

template <class T1, class T2>
inline void CoordPoint<T1, T2>::Print() const {
   cout << "X = " << X << ", Y = " << Y;
}

template <class T1, class T2>
DisplayPoint<T1, T2>::DisplayPoint(T1 Px, T2 Py, unsigned int PColor) :
 CoordPoint<T1, T2>(Px, Py) {
   Color = PColor;
}

template <class T1, class T2>
inline void DisplayPoint<T1, T2>::Print() const {
   CoordPoint<T1, T2>::Print();
   cout << ", Color = " << Color;
}

template <class T1, class T2>
DisplayBrokenLine<T1, T2>::~DisplayBrokenLine() {
   for(unsigned int i=0; i<Length; i++)
      delete Nodes[i];
   delete [] Nodes;
}

template <class T1, class T2>
void DisplayBrokenLine<T1, T2>::Print() const {
   cout << "\nLine's color: " << LineColor << "." << endl
     << "Line's nodes:" << endl;
   for (unsigned int i=0; i<Length; i++) {
      cout << (i+1) << ". ";
      Nodes[i]->Print();
      cout << "." << endl;
   }
}

template <class T1, class T2>
void DisplayBrokenLine<T1, T2>::AddNode(const DisplayPoint<T1, T2>& Node) {
   if (Length == MaxSize)
      throw OverflowException();
   else
      Nodes[Length++] = new DisplayPoint<T1, T2>(
        Node.GetX(), Node.GetY(), Node.GetColor()
      );
}


int main(void) {
   DisplayBrokenLine<int, long>  *IntLongLine  = 
     new DisplayBrokenLine<int, long>(2, 1);
   DisplayBrokenLine<long, long> *LongLongLine = 
     new DisplayBrokenLine<long, long>(2, 1);

   DisplayPoint<int, long>   *IntLongD1  = new DisplayPoint<int, long>(10, 11, 12);
   DisplayPoint<long, long>  *LongLongD1 = new DisplayPoint<long, long>(10L, 11L, 12);

   DisplayPoint<int, long>   IntLongD2(13, 14, 15);
   DisplayPoint<long, long>  LongLongD2(13L, 14L, 15);

   try {
      IntLongLine->AddNode(*IntLongD1);
      cout << "\nNew INT, LONG node has been added successfully!" << endl;
   }
      catch (OverflowException&) {
         cout << "Error: maximal size exceeded!" << endl;
      }
      catch (...) {
         cout << "Unknown Error!" << endl;
      }

   try {
      IntLongLine->AddNode(IntLongD2);
      cout << "\nNew INT, LONG node has been added successfully!" << endl;
   }
      catch (OverflowException&) {
         cout << "Error: maximal size exceeded!" << endl;
      }
      catch (...) {
         cout << "Unknown Error!" << endl;
      }

   try {
      LongLongLine->AddNode(*LongLongD1);
      cout << "\nNew LONG, LONG node has been added successfully!" << endl;
   }
      catch (OverflowException&) {
         cout << "Error: maximal size exceeded!" << endl;
      }
      catch (...) {
         cout << "Unknown Error!" << endl;
      }

   try {
      LongLongLine->AddNode(LongLongD2);
      cout << "\nNew LONG, LONG node has been added successfully!" << endl;
   }
      catch (OverflowException&) {
         cout << "Error: maximal size exceeded!" << endl;
      }
      catch (...) {
         cout << "Unknown Error!" << endl;
      }

   delete IntLongD1;
   delete LongLongD1;
      
   cout << endl << "INT, LONG line:";
   IntLongLine->Print();

   cout << endl << "LONG, LONG line:";
   LongLongLine->Print();

   delete IntLongLine;
   delete LongLongLine;

   cin.get();
   return 0;
}
