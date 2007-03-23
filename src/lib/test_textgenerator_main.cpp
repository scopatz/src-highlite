#include "textgenerator.h"
#include "textstylebuilder.h"
#include "doctemplate.h"
#include "asserttest.h"

using namespace std;

int
main()
{
	int result = 0;
	
	TextStyle bold("<b>$text</b>");
	TextStyle italics("<i>$text</i>");
	
	TextStyle keyword = bold;
	TextGenerator keywordGenerator(keyword);
	
	string orig = "fookeyword";
	string expected = "<b>" + orig + "</b>";
	string transformed = keywordGenerator.generateEntire(orig);
	
	cout << "orig: " << orig << endl;
	cout << "transformed: " << transformed << endl;
	
	result += assertEquals(expected, transformed);
	
	TextStyle keyword2 = bold.compose(italics);
	TextGenerator keywordGenerator2(keyword2);

	expected = "<b><i>" + orig + "</i></b>";
	transformed = keywordGenerator2.generateEntire(orig);
	
	cout << "orig: " << orig << endl;
	cout << "transformed: " << transformed << endl;
	
	result += assertEquals(expected, transformed);
	
	TextStyleBuilder textStyleBuilder;
    
    textStyleBuilder.start();
    textStyleBuilder.add(bold);
    textStyleBuilder.add(italics);
    TextGenerator keywordGenerator3(textStyleBuilder.end());
    
    expected = "<b><i>" + orig + "</i></b>";
	transformed = keywordGenerator3.generateEntire(orig);
	
	cout << "orig: " << orig << endl;
	cout << "transformed: " << transformed << endl;
	
	result += assertEquals(expected, transformed);
	
	TextStyleBuilder textStyleBuilder2("start{" STYLE_VAR_TEXT TEXT_VAR_TEXT "}", ";");
	textStyleBuilder2.start();
	textStyleBuilder2.add(TextStyle("bold" STYLE_VAR_TEXT));
	textStyleBuilder2.add(TextStyle("italics " STYLE_VAR_TEXT));
	TextGenerator keywordGenerator4(textStyleBuilder2.end());
	
	expected = "start{bold;italics " + orig + "}";
	transformed = keywordGenerator4.generateEntire(orig);
	
	cout << "orig: " << orig << endl;
	cout << "transformed: " << transformed << endl;
	
	result += assertEquals(expected, transformed);	
    
    string start = "$headerthe title: $title\nthe css url: $css\nand some additional text: $additional";
    string end = "$footer";
    string expected_start = "HEADER\nthe title: TITLE\nthe css url: CSS\nand some additional text: ADDITIONAL";
    string expected_end = "\nFOOTER";
    DocTemplate docTemplate(start, end);

    string transformed_start = docTemplate.output_begin("TITLE", "CSS", "ADDITIONAL", "HEADER\n", "\nFOOTER", "");
    string transformed_end = docTemplate.output_end("TITLE", "CSS", "ADDITIONAL", "HEADER\n", "\nFOOTER", "");
    
    cout << "orig start : " << start << endl;
    cout << "transformed: " << transformed_start << endl;
    result += assertEquals(expected_start, transformed_start);

    cout << "orig end   : " << end << endl;
    cout << "transformed: " << transformed_end << endl;
    result += assertEquals(expected_end, transformed_end);
		
	return result;	
}
