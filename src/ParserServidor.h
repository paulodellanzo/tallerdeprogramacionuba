#ifndef PARSERSERVIDOR_H_
#define PARSERSERVIDOR_H_

using namespace std;
#include <string>

class ParserServidor {
public:
	ParserServidor();
	string getRespuesta(string Xml);
	virtual ~ParserServidor();
};

#endif /* PARSERSERVIDOR_H_ */
