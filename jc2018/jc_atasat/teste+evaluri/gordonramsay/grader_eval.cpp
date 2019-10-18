#include <bits/stdc++.h>

const long long INF = 100000000000000000LL;

//********************************ERROR HANDLING**********************************
enum Errors {
  OK,
  BAD_OUTPUT,
  BAD_COST,
  NONOPTIMAL,
  NO_INPUT,
  NO_OUTPUT,
  NO_OK,
  BAD_OK
};

const char* msg[8] = {"Delicios!", "Dezastru total!", "Dosar penal pentru evaziune fiscala!", "Se poate mai bine!", "Fisierul de intrare lipsa!", "Fisierul de iesire lipsa!", "Fisierul .ok lipsa!", "Solutie mai buna decat a comisiei!"};

struct ErrorHandler {
private:
  Errors err;

public:
  ErrorHandler() {
    err = OK;
  }

  void setError(Errors error) {
    err = error;
    this->giveScore();
  }

  void giveScore() {
    if(err == OK)
      printf("5");
    else if(err == BAD_OK) // This should not happen
      printf("10");
    else
      printf("0");
    fprintf(stderr, "%s", msg[err]);

    exit(0);
  }
};

//*************************************FILE HANDLING***************************************

struct Aliment {
  int cost, profit, rezist;
};

struct Input {
private:
  int n, k;
  int *comenzi;
  Aliment *food;
  FILE *fin;

public:
  // Citire input
  Input(const char *name, ErrorHandler *handler) {
    this->fin = fopen(name, "r");

    if(this->fin == NULL)
      handler->setError(NO_INPUT);

    fscanf(this->fin, "%d%d", &this->n, &this->k);

    this->comenzi = new int[this->n];
    this->food = new Aliment[this->k];

    for(int i = 0; i < n; ++i) {
      fscanf(this->fin, "%d", &this->comenzi[i]);
      --this->comenzi[i];
    }

    for(int i = 0; i < k; ++i)
      fscanf(this->fin, "%d%d%d", &this->food[i].cost, &this->food[i].profit, &this->food[i].rezist);
  }
  ~Input() {
    delete[] this->comenzi;
    delete[] this->food;

    if(this->fin != NULL)
      fclose(this->fin);
  }

  int getK() {
    return this->k;
  }
  int getN() {
    return this->n;
  }
  int getComanda(int i) {
    return this->comenzi[i];
  }
  Aliment getAliment(int i) {
    return this->food[i];
  }
};

struct Output {
private:
  long long profitmax;
  int t;
  int *x;
  FILE *fin;
  char cursor;

  // Verifica validitatea profitului
  void checkProfit(Input* inp, ErrorHandler* errHandle) {
    int *cant = new int[inp->getK()];
    long long cost = 0LL;

    for(int i = 0; i < inp->getN(); ++i) {
      if(i % this->t == 0) {
        for(int j = 0; j < inp->getK(); ++j) {
          cant[j] = this->x[j];
          cost = cost - (long long)this->x[j] * inp->getAliment(j).cost;
        }
      }

      if(i % this->t < inp->getAliment(inp->getComanda(i)).rezist && cant[inp->getComanda(i)] > 0) {
        cost = cost + inp->getAliment(inp->getComanda(i)).profit;
        cant[inp->getComanda(i)]--;
      }
    }

    delete[] cant;
    
    if(cost != this->profitmax)
      errHandle->setError(BAD_COST);
  }

  char getch() {
    this->cursor = fgetc(fin);
    while(this->cursor == ' ')
      this->cursor = fgetc(fin);
    return this->cursor;
  }

  void getnr(long long &x) {
    x = 0LL;
    this->cursor = this->getch();
    if(!isdigit(cursor)) {
      x = -1;
      return ;
    }

    while(isdigit(cursor) && x < INF) {
      x = x * 10 + this->cursor - '0';
      this->cursor = fgetc(fin);
    }

    if(this->cursor != ' ' && this->cursor != '\n') {
      x = -1;
      return;
    }
  }

  void getnr(int &x) {
    long long aux;
    this->getnr(aux);
    if(aux > 1000000000)
      x = -1;
    else
      x = aux;
  }

  bool endOfLine() {
    while(this->cursor == ' ')
      this->cursor = fgetc(fin);
    return this->cursor == '\n';
  }

  bool endOfFile() {
    while(this->cursor == ' ' || this->cursor == '\n')
      this->cursor = fgetc(fin);
    return this->cursor == EOF;
  }

public:
  // Citire output
  Output(const char *name, Input* input, ErrorHandler* handler, bool okfile = false) {
    x = new int[input->getK()];

    this->fin = fopen(name, "r");
        
    if(this->fin == NULL && okfile)
      handler->setError(NO_OK);
    else if(this->fin == NULL)
      handler->setError(NO_OUTPUT);
    
    this->getnr(this->profitmax);
    if(this->profitmax == -1)
      handler->setError(BAD_OUTPUT);
    
    if(!this->endOfLine())
      handler->setError(BAD_OUTPUT);
    
    this->getnr(this->t);
    if(this->t <= 0 || this->t > input->getN())
      handler->setError(BAD_OUTPUT);

    if(!this->endOfLine())
      handler->setError(BAD_OUTPUT);

    for(int i = 0; i < input->getK(); ++i) {
      this->getnr(this->x[i]);
      if(this->x[i] == -1)
        handler->setError(BAD_OUTPUT);
    }

    if(!this->endOfFile())
      handler->setError(BAD_OUTPUT);

    this->checkProfit(input, handler);
  }

  ~Output() {
    if(fin != NULL)
      fclose(fin);

    delete[] x;
  }

  long long getProfit() {
    return this->profitmax;
  }
};

int main() {
  ErrorHandler *handler = new ErrorHandler();
  Input *in = new Input("gordonramsay.in", handler);
  Output *out = new Output("gordonramsay.out", in, handler), *ok = new Output("gordonramsay.ok", in, handler);
  if(out->getProfit() < ok->getProfit())
    handler->setError(NONOPTIMAL);
  else if(out->getProfit() > ok->getProfit())
    handler->setError(BAD_OK);
  else
    handler->setError(OK);
  
  return 0;
}
