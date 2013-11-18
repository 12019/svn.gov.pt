//========================================================================
//
// Catalog.cc
//
// Copyright 1996-2007 Glyph & Cog, LLC
//
//========================================================================

//========================================================================
//
// Modified under the Poppler project - http://poppler.freedesktop.org
//
// All changes made under the Poppler project to this file are licensed
// under GPL version 2 or later
//
// Copyright (C) 2005 Kristian Høgsberg <krh@redhat.com>
// Copyright (C) 2005-2011 Albert Astals Cid <aacid@kde.org>
// Copyright (C) 2005 Jeff Muizelaar <jrmuizel@nit.ca>
// Copyright (C) 2005 Jonathan Blandford <jrb@redhat.com>
// Copyright (C) 2005 Marco Pesenti Gritti <mpg@redhat.com>
// Copyright (C) 2005, 2006, 2008 Brad Hards <bradh@frogmouth.net>
// Copyright (C) 2006, 2008, 2011 Carlos Garcia Campos <carlosgc@gnome.org>
// Copyright (C) 2007 Julien Rebetez <julienr@svn.gnome.org>
// Copyright (C) 2008, 2011 Pino Toscano <pino@kde.org>
// Copyright (C) 2009 Ilya Gorenbein <igorenbein@finjan.com>
// Copyright (C) 2010 Hib Eris <hib@hiberis.nl>
//
// To see a description of the changes please see the Changelog file that
// came with your tarball or type make ChangeLog if you are building from git
//
//========================================================================

#include <config.h>

#ifdef USE_GCC_PRAGMAS
#pragma implementation
#endif

#ifdef _WIN32
#define _CRT_RAND_S
#else 
#include <unistd.h>
#include <fcntl.h>
#endif

#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include "goo/gmem.h"
#include "Object.h"
#include "PDFDoc.h"
#include "XRef.h"
#include "Array.h"
#include "Dict.h"
#include "Page.h"
#include "Error.h"
#include "Link.h"
//#include "DeflateStream.h"
#include "PageLabelInfo.h"
#include "Catalog.h"
#include "Form.h"
#include "OptionalContent.h"
#include "ViewerPreferences.h"
#include "FileSpec.h"
#include "BuiltinFontTables.h"
#include "BuiltinFontTables.h"
#include "BuiltinFont.h"
#include "FontEncodingTables.h"
#include "VisibleSignatureBitmap.h"
#include "Myriad-Font.h"

//Forward-declaration of the function defined in Iconv.cc
//couldn't bother to write a header for it
extern char *utf8_to_latin1(const char *str);

//------------------------------------------------------------------------
// Catalog
//------------------------------------------------------------------------

Catalog::Catalog(PDFDoc *docA) {
  Object pagesDict, pagesDictRef;
  Object obj, obj2;
  Object optContentProps;

  ok = gTrue;
  doc = docA;
  xref = doc->getXRef();
  pages = NULL;
  pageRefs = NULL;
  numPages = -1;
  pagesSize = 0;
  baseURI = NULL;
  pageLabelInfo = NULL;
  form = NULL;
  optContent = NULL;
  pageMode = pageModeNull;
  pageLayout = pageLayoutNull;
  destNameTree = NULL;
  embeddedFileNameTree = NULL;
  jsNameTree = NULL;
  viewerPrefs = NULL;

  pagesList = NULL;
  pagesRefList = NULL;
  attrsList = NULL;
  kidsIdxList = NULL;
  lastCachedPage = 0;


  xref->getCatalog(&catDict);
   
  if (!catDict.isDict()) {
    error(errSyntaxError, -1, "Catalog object is wrong type ({0:s})", catDict.getTypeName());
    goto err1;
  }
  // get the AcroForm dictionary
  catDict.dictLookup("AcroForm", &acroForm);

  // read base URI
  if (catDict.dictLookup("URI", &obj)->isDict()) {
    if (obj.dictLookup("Base", &obj2)->isString()) {
      baseURI = obj2.getString()->copy();
    }
    obj2.free();
  }
  obj.free();

  // get the Optional Content dictionary
  if (catDict.dictLookup("OCProperties", &optContentProps)->isDict()) {
    optContent = new OCGs(&optContentProps, xref);
    if (!optContent->isOk ()) {
      delete optContent;
      optContent = NULL;
    }
  }
  optContentProps.free();

  // get the ViewerPreferences dictionary
  catDict.dictLookup("ViewerPreferences", &viewerPreferences);
  //catDict.free();
  return;

 err1:
  catDict.free();
  ok = gFalse;
}

Catalog::~Catalog() {
  delete kidsIdxList;
  if (attrsList) {
    std::vector<PageAttrs *>::iterator it;
    for (it = attrsList->begin() ; it < attrsList->end(); it++ ) {
      delete *it;
    }
    delete attrsList;
  }
  delete pagesRefList;
  if (pagesList) {
    std::vector<Dict *>::iterator it;
    for (it = pagesList->begin() ; it < pagesList->end(); it++ ) {
      if (!(*it)->decRef()) {
         delete *it;
      }
    }
    delete pagesList;
  }
  if (pages) {
    for (int i = 0; i < pagesSize; ++i) {
      if (pages[i]) {
	delete pages[i];
      }
    }
    gfree(pages);
    gfree(pageRefs);
  }
  names.free();
  dests.free();
  delete destNameTree;
  delete embeddedFileNameTree;
  delete jsNameTree;
  if (baseURI) {
    delete baseURI;
  }
  delete pageLabelInfo;
  delete form;
  delete optContent;
  delete viewerPrefs;
  metadata.free();
  structTreeRoot.free();
  outline.free();
  acroForm.free();
  viewerPreferences.free();
}


void Catalog::setIncrementalSignature(bool incremental)
{
	incremental_update = incremental;

}

#ifdef _WIN32
unsigned int getBigRandom()
{
	unsigned int tmp =0;
	errno_t err;
	
	err = rand_s(&tmp);
	if (err)
	{
		fprintf (stderr, "rand_s (1) failed, using rand() as fallback!\n");
		srand(time(NULL));
		return rand();

	}
	return tmp;

}
#else
unsigned int getBigRandom()
{
	unsigned int res=0;
	int ret_read = 0;

	int fd = open("/dev/urandom", O_RDONLY);

	if (fd == -1)
	{
		//TODO: get/translate errno
		fprintf(stderr, "Failed to open /dev/urandom, using rand() as fallback!\n");
		goto fallback;
	}
	ret_read = read(fd, &res, sizeof(res));
	close(fd);
	if (ret_read == -1)
	{
		fprintf(stderr, "Failed to open /dev/urandom, using rand() as fallback!\n");
		goto fallback;
	}
	return res;

fallback:
	srand(time(NULL));
	return rand();
}

#endif


//TODO: Too long, split this into 2 functions at least
void Catalog::prepareSignature(PDFRectangle *rect, const char * name, Ref *firstPageRef,
	       	const char *location, const char *civil_number,
		const char *reason, unsigned long filesize, int page, int sig_sector) 
{

	Object signature_field;
	Object *signature_dict = new Object();
	Object acroform;

	char date_outstr[200];
	time_t t;
	struct tm *tmp_date;
	double r0=0, r1=0, r2=0, r3=0;

	t = time(NULL);
	tmp_date = localtime(&t);
	//Date String for visible signature
	strftime(date_outstr, sizeof(date_outstr), "%Y.%m.%d %H:%M:%S %z", tmp_date);

	signature_field.initDict(xref);
	Object obj1, obj2, obj3, obj4, obj5, obj6, ref_to_dict;

	/* Fill the signature formfield dict key-value pairs */
	signature_field.dictAdd(copyString("Type"), obj1.initName("Annot"));
	signature_field.dictAdd(copyString("Subtype"), obj2.initName("Widget"));
	signature_field.dictAdd(copyString("FT"), obj3.initName("Sig"));

	/* Annotation Flags: Hidden and Locked (bits 1 and 8 counting from
	 * lowest order bit as 1)  */
	signature_field.dictAdd(copyString("F"), obj3.initInt(132));
	signature_field.dictAdd(copyString("SigSector"), obj3.initInt(sig_sector));

	obj4.initArray (xref);
	
	//Visible Signature location 
	if (rect)
	{
				
		r0=rect->x1;
	       	r1=rect->y1;
	       	r2=rect->x2; 
		r3=rect->y2;
	}
	obj4.arrayAdd (obj2.initReal(r0));
	obj4.arrayAdd (obj2.initReal(r1));
	obj4.arrayAdd (obj2.initReal(r2));
	obj4.arrayAdd (obj2.initReal(r3));

	signature_field.dictAdd(copyString("Rect"), &obj4);

	signature_field.dictAdd(copyString("T"), obj2.initString(GooString::format("Signature{0:ud}", 
					getBigRandom())));

	addSignatureAppearance(&signature_field, name, civil_number, date_outstr,
		 location, reason, r2-r0 - 1, r3-r1 -1);

	memset(date_outstr, 0, sizeof(date_outstr));

	Ref *refFirstPage = firstPageRef != NULL ? firstPageRef: &(pageRefs[page-1]);

	Object ref_to_first_page;
	/*
	  Init a placeholder string;
	  This needs to be present in preparation phase to make sure all the
	  offsets in the XRef table are unchanged when the real signature is
	  added
	*/
	char * placeholder = (char *)gmalloc(PLACEHOLDER_LEN+1);
	memset(placeholder, '0', PLACEHOLDER_LEN);
	placeholder[PLACEHOLDER_LEN] = '\0';

	ref_to_first_page.initRef(refFirstPage->num, refFirstPage->gen);

	signature_field.dictAdd(copyString("P"), &ref_to_first_page);

	signature_dict->initSignatureDict(xref);
	
	GooString * sig_content = new GooString(placeholder);
	sig_content->setHexString();
	signature_dict->dictAdd(copyString("Type"), obj3.initName("Sig"));

	signature_dict->dictAdd(copyString("Contents"), obj1.initString(sig_content));
	signature_dict->dictAdd(copyString("SubFilter"), obj1.initName("adbe.pkcs7.detached"));
	signature_dict->dictAdd(copyString("Name"), obj1.initString(new GooString(utf8_to_latin1(name))));
	const char *loc = location != NULL ? utf8_to_latin1(location) : "";
	signature_dict->dictAdd(copyString("Location"), obj1.initString(new GooString(loc)));
	const char *rea = reason != NULL ? utf8_to_latin1(reason): "";
	signature_dict->dictAdd(copyString("Reason"), obj1.initString(new GooString(rea)));
	if (strftime(date_outstr, sizeof(date_outstr), "D:%Y%m%d%H%M%S+00'00'", tmp_date) == 0) {
               fprintf(stderr, "strftime returned 0");
        }
	else
		signature_dict->dictAdd(copyString("M"), obj1.initString(new GooString(date_outstr)));

	signature_dict->dictAdd(copyString("Filter"), obj1.initName("Adobe.PPKLite"));

	m_sig_dict = signature_dict;

	Ref ref_to_sigdict = xref->addIndirectObject(signature_dict);

	m_sig_ref.gen = ref_to_sigdict.gen;
	m_sig_ref.num = ref_to_sigdict.num;

	ref_to_dict.initRef (ref_to_sigdict.num, ref_to_sigdict.gen);
	signature_field.dictAdd (copyString("V"), &ref_to_dict);


	Ref sig_ref = xref->addIndirectObject(&signature_field);

	Object local_acroForm, fields_array, ref_to_sig;

	ref_to_sig.initRef(sig_ref.num, sig_ref.gen);

	addSigRefToPage(refFirstPage, &ref_to_sig);

	catDict.dictLookup("AcroForm", &local_acroForm);

	Object acroForm_ref;

	//PDF File has no AcroForm dict, we need to create it
	if (!local_acroForm.isDict())
	{

		Object fields;
		acroform.initDict(xref);
		fields.initArray(xref);

		acroform.dictAdd(copyString("Fields"), &fields);
		acroform.dictAdd(copyString("SigFlags"), obj2.initInt(3));
		//catDict.dictAdd(copyString("AcroForm"), &acroform);
		local_acroForm = acroform;
	}
	else
	{
		catDict.dictLookupNF("AcroForm", &acroForm_ref);
		
		fprintf(stderr, "local_acroform is a dict!\n");
		setSigFlags(&local_acroForm, 3);

	}

	Object o1;
	o1.initNull();
	//Remove NeedApperances field if present
	local_acroForm.dictSet(copyString("NeedAppearances"), &o1);

	local_acroForm.dictLookup("Fields", &fields_array);
	if (fields_array.isArray())
	{
		fprintf(stderr, "Fields array found adding signature field\n");
		Object fields_ref;
		local_acroForm.dictLookupNF("Fields", &fields_ref);
		fields_array.arrayAdd(&ref_to_sig);

		if (fields_ref.isRef())
		{
			fprintf(stderr, "Fields array is an indirect object...\n");
			xref->setModifiedObject(&fields_array, fields_ref.getRef());

		}
	}

	//Set the catalog object as modified to force rewrite
	Ref catalog_ref;
	catalog_ref.gen = xref->getRootGen();
	catalog_ref.num = xref->getRootNum();
	catDict.dictAdd(copyString("AcroForm"), &local_acroForm);

	//By the spec we should be handling the case
	//where the acroform object is compressed and we're doing 
	//an incremental update to sign. For now it works as is...
	/*
	if (m_is_compressed) // && is_incremental
	{
		DeflateStream *str = new DeflateStream(&catDict);
		Object obj_stream;
		obj_stream.initStream(str);
		xref->addIndirectObject(&obj_stream);
	}
	*/
	if (acroForm_ref.isRef())
	{
		xref->setModifiedObject(&local_acroForm, acroForm_ref.getRef());
		fprintf(stderr, "AcroForm is an indirect object so we'll just update it...\n");

	}

	else if(!incremental_update)
		xref->setModifiedObject(&catDict, catalog_ref);


}

/*
 * return value is the number of padding spaces to be added
 * (Estimated Max Size - Actual_Size of /ByteRange Entry)
 */
int Catalog::setSignatureByteRange(unsigned long sig_contents_offset, unsigned
		long estimated_len, unsigned long filesize) {
	unsigned int padded_byterange_len = 100;
	Object obj, obj2;
	char tmp[100];
	int off2 = sig_contents_offset;
	int off3 = sig_contents_offset + estimated_len +2;
	int off4 = filesize-sig_contents_offset-estimated_len-2+
				padded_byterange_len;
	obj.initArray(xref);
	obj.arrayAdd(obj2.initInt(0));
	obj.arrayAdd(obj2.initInt(off2));
	obj.arrayAdd(obj2.initInt(off3)); //The estimated siglen *2 (hex string) plus <> delimiters

	obj.arrayAdd(obj2.initInt(off4)); //This is correct if the updated ByteRange has the same number of chars

	m_sig_dict->dictSet(copyString("ByteRange"), &obj);

	int actual_size = snprintf(tmp, sizeof(tmp),
		       	"/ByteRange [0 %d %d %d ] ", off2, off3, off4);

	SignatureDict *d = dynamic_cast<SignatureDict *>(m_sig_dict->getDict());
	d->setPadding(padded_byterange_len - actual_size);

	xref->setModifiedObject(m_sig_dict, m_sig_ref);

	return padded_byterange_len - actual_size;
}

void Catalog::closeSignature(const char * signature_contents, unsigned long len)
{
	Object obj;
	char * padded_string = (char *)gmalloc(len+1);

	if (signature_contents == NULL)
	{
      		error(errInternal, -1, "closeSignature(): Signature object is NULL!");
		return;
	}

	if (strlen(signature_contents) > len)
      		error(errInternal, -1, "Signature length is greater than allocated buffer!");

	memset(padded_string, '0', len);
	padded_string[len] = 0;

	memcpy(padded_string, signature_contents, strlen(signature_contents));

	GooString * sig_content = new GooString(padded_string);
	sig_content->setHexString();

	m_sig_dict->dictSet(copyString("Contents"), obj.initString(sig_content));

	xref->setModifiedObject(m_sig_dict, m_sig_ref);
}

GBool Catalog::addSigRefToPage(Ref * refPage, Object* sig_ref)
{
	Object page, annots, tmp_ref;
	xref->fetch(refPage->num, refPage->gen, &page);

	Dict *pageDict = page.getDict();

	pageDict->lookup("Annots", &annots);

	if (!annots.isArray())
	{
		annots.initArray(xref);
		page.dictSet("Annots", &annots);
	}
	else
	{

	    pageDict->lookupNF("Annots", &tmp_ref);

	}

	annots.arrayAdd(sig_ref);

	if (tmp_ref.isRef())
	{
		xref->setModifiedObject(&annots, tmp_ref.getRef());
	}
	else
	{
		xref->setModifiedObject(&page, *refPage);
	}

	return gTrue;
}

/**
* Creates an XObject with plain text content stream for the Visual Signature N0 and N2 Layers
* For the N2 layer it adds the needed fonts and image.
*
*/
Ref Catalog::newXObject(char *plain_text_stream, int height, int width, bool needs_font, bool needs_image)
{
	Object * appearance_obj = new Object();
	Object obj1, obj2, font_dict, ref_to_dict, ref_to_dict2, 
	       ref_to_dict3;

	appearance_obj->initDict(xref);
	appearance_obj->dictAdd(copyString("Type"), obj1.initName("XObject"));

	Object procset, resources;
	procset.initArray(xref);
	resources.initDict(xref);
	procset.arrayAdd(obj1.initName("PDF"));
	procset.arrayAdd(obj1.initName("Text"));
	procset.arrayAdd(obj1.initName("ImageB"));
	procset.arrayAdd(obj1.initName("ImageC"));
	procset.arrayAdd(obj1.initName("ImageI"));
	resources.dictAdd(copyString("ProcSet"), &procset);

	if (needs_font)
	{

		Object myriad_regular = createMyriadDict(xref, MYRIAD_REGULAR);
		Object myriad_italic = createMyriadDict(xref, MYRIAD_ITALIC);
		Object myriad_bold = createMyriadDict(xref, MYRIAD_BOLD);

		Ref font_f1 = xref->addIndirectObject(&myriad_regular);
		Ref font_f2 = xref->addIndirectObject(&myriad_italic);
		Ref font_f3 = xref->addIndirectObject(&myriad_bold);
		ref_to_dict.initRef(font_f1.num, font_f1.gen);
		ref_to_dict2.initRef(font_f2.num, font_f2.gen);
		ref_to_dict3.initRef(font_f3.num, font_f3.gen);

		font_dict.initDict(xref);
		font_dict.dictAdd(copyString("F1"), &ref_to_dict);
		font_dict.dictAdd(copyString("F2"), &ref_to_dict2);
		font_dict.dictAdd(copyString("F3"), &ref_to_dict3);
		resources.dictAdd(copyString("Font"), &font_dict);

	}

	if (needs_image)
	{
		//Get the Cartao de Cidadao logo already encoded as JPEG
		Ref image_background = addImageXObject(cc_logo_bitmap_width, cc_logo_bitmap_height, cc_logo_bitmap_compressed,
				sizeof(cc_logo_bitmap_compressed));

		ref_to_dict.initRef(image_background.num, image_background.gen);
		Object image_dict;
		image_dict.initDict(xref);
		image_dict.dictAdd(copyString("Im0"), &ref_to_dict);

		resources.dictAdd(copyString("XObject"), &image_dict);

	}

	appearance_obj->dictAdd(copyString("Resources"), &resources);
	appearance_obj->dictAdd(copyString("Subtype"), obj1.initName("Form"));

	obj1.initArray(xref);
	// BBox gives the coordinates (left, bottom, right, top) of the
	// Signature Rectangle relative to its origin point
	obj1.arrayAdd(obj2.initReal(0));
	obj1.arrayAdd(obj2.initReal(0));
	obj1.arrayAdd(obj2.initReal(height));
	obj1.arrayAdd(obj2.initReal(width));
	appearance_obj->dictAdd(copyString("BBox"), &obj1);
	appearance_obj->dictAdd(copyString("Length"),
	obj1.initInt(strlen(plain_text_stream))); 

	MemStream *mStream = new MemStream(strdup(plain_text_stream), 0,
			strlen(plain_text_stream), appearance_obj);

	mStream->setNeedFree(gTrue);
	Object *aStream = new Object();
	aStream->initStream(mStream);

	Ref ref_to_appearance = xref->addIndirectObject(aStream);
	return ref_to_appearance;
}


Ref Catalog::addFontDict(const char *baseFontName, const char *font_name)
{

	Object font_dict, name;
	font_dict.initDict(xref);
	font_dict.dictAdd(copyString("BaseFont"), name.initName(baseFontName));
	font_dict.dictAdd(copyString("Type"), name.initName("Font"));
	font_dict.dictAdd(copyString("Encoding"), name.initName("WinAnsiEncoding"));
	font_dict.dictAdd(copyString("Subtype"), name.initName("Type1"));
	//TODO: should be generated??
	font_dict.dictAdd(copyString("Name"), name.initName(font_name));

	Ref ref_to_appearance = xref->addIndirectObject(&font_dict);

	return ref_to_appearance;
}

Ref Catalog::addImageXObject(int width, int height, unsigned char *data, int length_in_bytes)
{

	Object * image_obj = new Object();
	Object obj1, obj2;

	image_obj->initDict(xref);
	image_obj->dictAdd(copyString("Type"), obj1.initName("XObject"));
	image_obj->dictAdd(copyString("Subtype"), obj1.initName("Image"));
	image_obj->dictAdd(copyString("ColorSpace"), obj1.initName("DeviceRGB"));
	image_obj->dictAdd(copyString("BitsPerComponent"), obj1.initInt(8));
	image_obj->dictAdd(copyString("Width"), obj1.initInt(width));
	image_obj->dictAdd(copyString("Height"), obj1.initInt(height));
	//We're adding a bitmap compressed with jpeg, which is what DCTDecode means
	image_obj->dictAdd(copyString("Filter"), obj2.initName("DCTDecode"));
	image_obj->dictAdd(copyString("Length"), obj1.initInt(length_in_bytes));

	MemStream *mStream = new MemStream((char *)data, 0,
			length_in_bytes, image_obj);

	mStream->setNeedFree(gTrue);
	Object *aStream = new Object();
	aStream->initStream(mStream);

	Ref ref_to_appearance = xref->addIndirectObject(aStream);
	return ref_to_appearance;
}

/*
 * Get the exact widths of the glyphs necessary to represent
 * our text in our chosen font-face and fontsize
 * Units: postscript points (pts)
 */
double getStringWidth(const char *winansi_encoded_string, double font_size, MyriadFontType font)
{
    double total_width = 0;
    unsigned int w = 0;
    unsigned char code = 0;

    //Lookup each winansi char width 
    for (unsigned int i = 0; i!= strlen(winansi_encoded_string); i++)
    {
       code = (unsigned char)winansi_encoded_string[i];
       w = getWidth(code, font);
	total_width += 0.001 * font_size * w;	 
    }

    return total_width;

}

std::string getFittingSubString(std::string &str, double font_size,
			   	MyriadFontType font, double space_available)
{
	int i = str.length() - 1;
	const double reserved = getStringWidth("(...)", font_size, font);
   	while(i >= 0)
	{
	    std::string tmp = str.substr(0, i);
	    if (getStringWidth(tmp.c_str(), font_size, font) <= 
						(space_available - reserved))
		return tmp;
		i--;

	}
	return "";
}

/*
 * Generate PDF text display commands according to a fixed-column
 * layout 
 */
GooString *formatMultilineString(char *content, double available_space, double font_size, MyriadFontType font,
	       int available_lines, double space_first_line=0)
{
	GooString *multi_line = new GooString();
	std::string line = std::string(content);
	std::string word;

	//Length of the ' ' char in current font and font-size
	double space_width = getWidth(' ', font) * font_size * 0.001; 	
	std::istringstream iss(line, std::istringstream::in);

	double space_left = space_first_line == 0 ? available_space : space_first_line;
	double word_width;
	/* Shift to the left to offset the left margin of the 
	first line if space_first_line > 0 */
	double horizontal_shift = -(available_space - space_first_line);
	int lines_used = 0, word_count = 0;

	multi_line->append("("); //Init String

	while( iss >> word)
	{
		word_width = getStringWidth(word.c_str(), font_size, font);
		//No more space in current line
		if (word_width + space_width > space_left)
		{
			lines_used++;
			
			if (word_count == 0)
			{
				multi_line->append(
						getFittingSubString(word, font_size, font, space_left).c_str());
				lines_used = available_lines;
			}

			if (lines_used == available_lines)
			{
			 //No more available lines so its an early exit...
			 multi_line->append("\\(...\\)) Tj \r\n");
			 return multi_line;

			}
			multi_line->append(") Tj\r\n");
			if (lines_used > 1 || space_first_line == 0)
				horizontal_shift = 0;

			//Line spacing
			multi_line->append(GooString::format("{0:f} -10 Td\r\n", horizontal_shift)); 
			//Space first line is only relevant for the 1st line
			space_first_line = 0;
			multi_line->append("("); 	  //Begin new line
			multi_line->append(word.c_str());
		
			//Reset space_left
			space_left = available_space - word_width;
		}
		else
		{
			if (multi_line->getLength() > 1)
				multi_line->append(" ");

			multi_line->append(word.c_str());
			space_left -= (word_width + space_width);

		}

		word_count++;

	}


	multi_line->append(") Tj\r\n");



	return multi_line;

}

void Catalog::addSignatureAppearance(Object *signature_field, const char *name, const char *civil_number,
	char * date_str, const char* location, const char* reason, int rect_x, int rect_y)
{
	Object ap_dict, appearance_obj, obj1, obj2, obj3,
	       ref_to_dict, ref_to_dict2, ref_to_n2, ref_to_n0, font_dict, xobject_layers;

	initBuiltinFontTables();
	
	const char appearance_command1[] = 
		"q 1 0 0 1 0 0 cm /n0 Do Q\r\nq 1 0 0 1 0 0 cm /n2 Do Q\r\n";
	
	char n0_commands[] = "% DSBlank\n";
	const float font_size = 8;
	//Start with Italics font
	GooString *n2_commands = new GooString(
           GooString::format("q\r\n175.5 0 0 31.5 0 0 cm\r\n/Im0 Do\r\nQ\r\nq 0.30588 0.54117 0.74509 rg\r\nBT\r\n0 {0:d} Td\r\n/F2 {1:d} Tf\r\n",
			rect_y - 10, (int)font_size));
	

	if (reason != NULL && strlen(reason) > 0)
	{
		GooString *abc = new GooString(utf8_to_latin1(reason));
		n2_commands->append(formatMultilineString(abc->getCString(), rect_x, font_size, MYRIAD_ITALIC, 2));
	}

	n2_commands->append("0 -10 Td\r\n");
	//Change font to regular black font
	n2_commands->append(GooString::format("0 0 0 rg\r\n/F1 {0:d} Tf\r\n",
			       	(int)font_size));

	double assinado_por_length = 51.0;
	//Change to bold font for the signer name
	n2_commands->append(GooString::format("(Assinado por: ) Tj\r\n{0:f} 0 Td\r\n/F3 {1:d} Tf\r\n",
		assinado_por_length, (int)font_size));
	
	//The parameter 5 in lines is intended to allow as much lines as needed to the name field	
	GooString *name_str = formatMultilineString(utf8_to_latin1(name), 
					rect_x, font_size, MYRIAD_BOLD, 5, rect_x - assinado_por_length);
	n2_commands->append(name_str);

	int lines = 0;
        char *haystack = name_str->getCString();
	while ((haystack = strstr(haystack, "Tj")) != NULL)
	{
		haystack += 2; //Skip current match of "Tj"
	       	lines++; 
	}

	if (lines < 2)
	{
		n2_commands->append(GooString::format("{0:f} -10 Td\r\n", -assinado_por_length)); 
	}
	else
		n2_commands->append("0 -10 Td\r\n");

	//Back to regular font
	n2_commands->append(GooString::format("/F1 {0:d} Tf\r\n", (int)font_size));

	n2_commands->append(GooString::format("(Num. de Identifica\xE7\xE3o Civil: {0:s}) Tj\r\n",
				civil_number));

	n2_commands->append(GooString::format("0 -10 Td\r\n(Data: {0:s}) Tj\r\n",
		date_str));

	if (location != NULL && strlen(location) > 0)
	{
		n2_commands->append("0 -10 Td\r\n");
		GooString * tmp_location = GooString::format("Localiza\xE7\xE3o: {0:s}",
					utf8_to_latin1(location));
		n2_commands->append(formatMultilineString(tmp_location->getCString(), 
					rect_x, font_size, MYRIAD_REGULAR, 1));
	}

	n2_commands->append("\r\nET\r\n");

	appearance_obj.initDict(xref);
	appearance_obj.dictAdd(copyString("Type"), obj1.initName("XObject"));
	appearance_obj.dictAdd(copyString("Subtype"), obj1.initName("Form"));
	Object procset, resources;
	procset.initArray(xref);
	resources.initDict(xref);
	/* Obsolete according to the spec since PDF 1.4 ?? */
        procset.arrayAdd(obj1.initName("PDF"));
	procset.arrayAdd(obj1.initName("Text"));
	procset.arrayAdd(obj1.initName("ImageB"));
	procset.arrayAdd(obj1.initName("ImageC"));
	procset.arrayAdd(obj1.initName("ImageI"));
	resources.dictAdd(copyString("ProcSet"), &procset);

	xobject_layers.initDict(xref);
	Ref n2_layer = newXObject(n2_commands->getCString(), rect_x, rect_y, true, true);
	ref_to_n2.initRef(n2_layer.num, n2_layer.gen);
	xobject_layers.dictAdd(copyString("n2"), &ref_to_n2);

	Ref n0_layer = newXObject(n0_commands, rect_x, rect_y, false, false);
	ref_to_n0.initRef(n0_layer.num, n0_layer.gen);
	xobject_layers.dictAdd(copyString("n0"), &ref_to_n0);

	resources.dictAdd(copyString("XObject"), &xobject_layers);

	//Adding /Resources to AP dict
	appearance_obj.dictAdd(copyString("Resources"), &resources);

	obj1.initArray(xref);

	// BBox gives the coordinates (left, bottom, right, top) of the
	// Signature Rectangle relative to its origin point
	obj1.arrayAdd(obj2.initReal(0));
	obj1.arrayAdd(obj2.initReal(0));
	obj1.arrayAdd(obj2.initReal(rect_x));
	obj1.arrayAdd(obj2.initReal(rect_y));
	appearance_obj.dictAdd(copyString("BBox"), &obj1);
	appearance_obj.dictAdd(copyString("Length"), 
			obj1.initInt(strlen(appearance_command1)));

	//appearance_obj.dictAdd(copyString("Filter"), obj1.initName("FlateDecode"));

	MemStream *mStream = new MemStream(strdup(appearance_command1), 0,
			sizeof(appearance_command1), &appearance_obj);

	mStream->setNeedFree(gTrue);
	Object aStream;
	aStream.initStream(mStream);

	Ref ref_to_appearance = xref->addIndirectObject(&aStream);
	ref_to_dict2.initRef(ref_to_appearance.num, ref_to_appearance.gen);

	ap_dict.initDict(xref);
	ap_dict.dictAdd(copyString("N"), &ref_to_dict2);
	
	signature_field->dictAdd(copyString("AP"), &ap_dict);

}


GBool Catalog::setSigFlags(Object * acroform, int value)
{
	Object obj1;	
	if (acroform->isDict())
	{

		Ref catalog_ref;
		catalog_ref.gen = xref->getRootGen();
		catalog_ref.num = xref->getRootNum();

		acroform->dictSet("SigFlags", obj1.initInt(value));

	}
	else
	{
		fprintf(stderr, "Error: cant add SigFlags. We need to create AcroForm first!\n");
		return gFalse;
	}

	return gTrue;
}

GooString *Catalog::readMetadata() {
  GooString *s;
  Dict *dict;
  Object obj;

  if (metadata.isNone()) {
    Object catDict;

    xref->getCatalog(&catDict);
    if (catDict.isDict()) {
      catDict.dictLookup("Metadata", &metadata);
    } else {
      error(errSyntaxError, -1, "Catalog object is wrong type ({0:s})", catDict.getTypeName());
      metadata.initNull();
    }
    catDict.free();
  }

  if (!metadata.isStream()) {
    return NULL;
  }
  dict = metadata.streamGetDict();
  if (!dict->lookup("Subtype", &obj)->isName("XML")) {
    error(errSyntaxWarning, -1, "Unknown Metadata type: '{0:s}'",
	  obj.isName() ? obj.getName() : "???");
  }
  obj.free();
  s = new GooString();
  metadata.getStream()->fillGooString(s);
  metadata.streamClose();
  return s;
}

Page *Catalog::getPage(int i)
{
  if (i < 1) return NULL;

  if (i > lastCachedPage) {
     if (cachePageTree(i) == gFalse) return NULL;
  }
  return pages[i-1];
}

Ref *Catalog::getPageRef(int i)
{
  if (i < 1) return NULL;

  if (i > lastCachedPage) {
     if (cachePageTree(i) == gFalse) return NULL;
  }
  return &pageRefs[i-1];
}

GBool Catalog::cachePageTree(int page)
{
  Dict *pagesDict;

  if (pagesList == NULL) {

    Object catDict;
    Ref pagesRef;

    xref->getCatalog(&catDict);

    if (catDict.isDict()) {
      Object pagesDictRef;
      if (catDict.dictLookupNF("Pages", &pagesDictRef)->isRef() &&
          pagesDictRef.getRefNum() >= 0 &&
          pagesDictRef.getRefNum() < xref->getNumObjects()) {
        pagesRef = pagesDictRef.getRef();
        pagesDictRef.free();
      } else {
        error(errSyntaxError, -1, "Catalog dictionary does not contain a valid \"Pages\" entry");
        pagesDictRef.free();
        catDict.free();
        return gFalse;
      }
    } else {
      error(errSyntaxError, -1, "Could not find catalog dictionary");
      catDict.free();
      return gFalse;
    }

    Object obj;
    catDict.dictLookup("Pages", &obj);
    catDict.free();
    // This should really be isDict("Pages"), but I've seen at least one
    // PDF file where the /Type entry is missing.
    if (obj.isDict()) {
      obj.getDict()->incRef();
      pagesDict = obj.getDict();
      obj.free();
    }
    else {
      error(errSyntaxError, -1, "Top-level pages object is wrong type ({0:s})", obj.getTypeName());
      obj.free();
      return gFalse;
    }

    pagesSize = getNumPages();
    pages = (Page **)gmallocn(pagesSize, sizeof(Page *));
    pageRefs = (Ref *)gmallocn(pagesSize, sizeof(Ref));
    for (int i = 0; i < pagesSize; ++i) {
      pages[i] = NULL;
      pageRefs[i].num = -1;
      pageRefs[i].gen = -1;
    }

    pagesList = new std::vector<Dict *>();
    pagesList->push_back(pagesDict);
    pagesRefList = new std::vector<Ref>();
    pagesRefList->push_back(pagesRef);
    attrsList = new std::vector<PageAttrs *>();
    attrsList->push_back(new PageAttrs(NULL, pagesDict));
    kidsIdxList = new std::vector<int>();
    kidsIdxList->push_back(0);
    lastCachedPage = 0;

  }

  while(1) {

    if (page <= lastCachedPage) return gTrue;

    if (pagesList->empty()) return gFalse;

    pagesDict = pagesList->back();
    Object kids;
    pagesDict->lookup("Kids", &kids);
    if (!kids.isArray()) {
      error(errSyntaxError, -1, "Kids object (page {0:d}) is wrong type ({1:s})",
            lastCachedPage+1, kids.getTypeName());
      kids.free();
      return gFalse;
    }

    int kidsIdx = kidsIdxList->back();
    if (kidsIdx >= kids.arrayGetLength()) {
       if (!pagesList->back()->decRef()) {
         delete pagesList->back();
       }
       pagesList->pop_back();
       pagesRefList->pop_back();
       delete attrsList->back();
       attrsList->pop_back();
       kidsIdxList->pop_back();
       if (!kidsIdxList->empty()) kidsIdxList->back()++;
       kids.free();
       continue;
    }

    Object kidRef;
    kids.arrayGetNF(kidsIdx, &kidRef);
    if (!kidRef.isRef()) {
      error(errSyntaxError, -1, "Kid object (page {0:d}) is not an indirect reference ({1:s})",
            lastCachedPage+1, kidRef.getTypeName());
      kidRef.free();
      kids.free();
      return gFalse;
    }

    GBool loop = gFalse;;
    for (size_t i = 0; i < pagesRefList->size(); i++) {
      if (((*pagesRefList)[i]).num == kidRef.getRefNum()) {
         loop = gTrue;
         break;
      }
    }
    if (loop) {
      error(errSyntaxError, -1, "Loop in Pages tree");
      kidRef.free();
      kids.free();
      kidsIdxList->back()++;
      continue;
    }

    Object kid;
    kids.arrayGet(kidsIdx, &kid);
    kids.free();
    if (kid.isDict("Page") || (kid.isDict() && !kid.getDict()->hasKey("Kids"))) {
      PageAttrs *attrs = new PageAttrs(attrsList->back(), kid.getDict());
      Page *p = new Page(doc, lastCachedPage+1, kid.getDict(),
                     kidRef.getRef(), attrs, form);
      if (!p->isOk()) {
        error(errSyntaxError, -1, "Failed to create page (page {0:d})", lastCachedPage+1);
        delete p;
        kidRef.free();
        kid.free();
        return gFalse;
      }

      if (lastCachedPage >= numPages) {
        error(errSyntaxError, -1, "Page count in top-level pages object is incorrect");
        kidRef.free();
        kid.free();
        return gFalse;
      }

      pages[lastCachedPage] = p;
      pageRefs[lastCachedPage].num = kidRef.getRefNum();
      pageRefs[lastCachedPage].gen = kidRef.getRefGen();

      lastCachedPage++;
      kidsIdxList->back()++;

    // This should really be isDict("Pages"), but I've seen at least one
    // PDF file where the /Type entry is missing.
    } else if (kid.isDict()) {
      attrsList->push_back(new PageAttrs(attrsList->back(), kid.getDict()));
      pagesRefList->push_back(kidRef.getRef());
      kid.getDict()->incRef();
      pagesList->push_back(kid.getDict());
      kidsIdxList->push_back(0);
    } else {
      error(errSyntaxError, -1, "Kid object (page {0:d}) is wrong type ({1:s})",
            lastCachedPage+1, kid.getTypeName());
      kidsIdxList->back()++;
    }
    kidRef.free();
    kid.free();

  }

  return gFalse;
}

int Catalog::findPage(int num, int gen) {
  int i;

  for (i = 0; i < getNumPages(); ++i) {
    Ref *ref = getPageRef(i+1);
    if (ref != NULL && ref->num == num && ref->gen == gen)
      return i + 1;
  }
  return 0;
}

LinkDest *Catalog::findDest(GooString *name) {
  LinkDest *dest;
  Object obj1, obj2;
  GBool found;

  // try named destination dictionary then name tree
  found = gFalse;
  if (getDests()->isDict()) {
    if (!getDests()->dictLookup(name->getCString(), &obj1)->isNull())
      found = gTrue;
    else
      obj1.free();
  }
  if (!found) {
    if (getDestNameTree()->lookup(name, &obj1))
      found = gTrue;
    else
      obj1.free();
  }
  if (!found)
    return NULL;

  // construct LinkDest
  dest = NULL;
  if (obj1.isArray()) {
    dest = new LinkDest(obj1.getArray());
  } else if (obj1.isDict()) {
    if (obj1.dictLookup("D", &obj2)->isArray())
      dest = new LinkDest(obj2.getArray());
    else
      error(errSyntaxWarning, -1, "Bad named destination value");
    obj2.free();
  } else {
    error(errSyntaxWarning, -1, "Bad named destination value");
  }
  obj1.free();
  if (dest && !dest->isOk()) {
    delete dest;
    dest = NULL;
  }

  return dest;
}

FileSpec *Catalog::embeddedFile(int i)
{
    Object efDict;
    Object obj;
    obj = getEmbeddedFileNameTree()->getValue(i);
    FileSpec *embeddedFile = 0;
    if (obj.isRef()) {
      Object fsDict;
      embeddedFile = new FileSpec(obj.fetch(xref, &fsDict));
      fsDict.free();
    } else {
      Object null;
      embeddedFile = new FileSpec(&null);
    }
    return embeddedFile;
}

GooString *Catalog::getJS(int i)
{
  Object obj;
  // getJSNameTree()->getValue(i) returns a shallow copy of the object so we
  // do not need to free it
  getJSNameTree()->getValue(i).fetch(xref, &obj);

  if (!obj.isDict()) {
    obj.free();
    return 0;
  }
  Object obj2;
  if (!obj.dictLookup("S", &obj2)->isName()) {
    obj2.free();
    obj.free();
    return 0;
  }
  if (strcmp(obj2.getName(), "JavaScript")) {
    obj2.free();
    obj.free();
    return 0;
  }
  obj2.free();
  obj.dictLookup("JS", &obj2);
  GooString *js = 0;
  if (obj2.isString()) {
    js = new GooString(obj2.getString());
  }
  else if (obj2.isStream()) {
    Stream *stream = obj2.getStream();
    js = new GooString();
    stream->fillGooString(js);
  }
  obj2.free();
  obj.free();
  return js;
}

Catalog::PageMode Catalog::getPageMode() {

  if (pageMode == pageModeNull) {

    Object catDict, obj;

    pageMode = pageModeNone;

    xref->getCatalog(&catDict);
    if (!catDict.isDict()) {
      error(errSyntaxError, -1, "Catalog object is wrong type ({0:s})", catDict.getTypeName());
      catDict.free();
      return pageMode;
    }

    if (catDict.dictLookup("PageMode", &obj)->isName()) {
      if (obj.isName("UseNone"))
        pageMode = pageModeNone;
      else if (obj.isName("UseOutlines"))
        pageMode = pageModeOutlines;
      else if (obj.isName("UseThumbs"))
        pageMode = pageModeThumbs;
      else if (obj.isName("FullScreen"))
        pageMode = pageModeFullScreen;
      else if (obj.isName("UseOC"))
        pageMode = pageModeOC;
      else if (obj.isName("UseAttachments"))
        pageMode = pageModeAttach;
    }
    obj.free();
    catDict.free();
  }
  return pageMode;
}

Catalog::PageLayout Catalog::getPageLayout() {

  if (pageLayout == pageLayoutNull) {

    Object catDict, obj;

    pageLayout = pageLayoutNone;

    xref->getCatalog(&catDict);
    if (!catDict.isDict()) {
      error(errSyntaxError, -1, "Catalog object is wrong type ({0:s})", catDict.getTypeName());
      catDict.free();
      return pageLayout;
    }

    pageLayout = pageLayoutNone;
    if (catDict.dictLookup("PageLayout", &obj)->isName()) {
      if (obj.isName("SinglePage"))
        pageLayout = pageLayoutSinglePage;
      if (obj.isName("OneColumn"))
        pageLayout = pageLayoutOneColumn;
      if (obj.isName("TwoColumnLeft"))
        pageLayout = pageLayoutTwoColumnLeft;
      if (obj.isName("TwoColumnRight"))
        pageLayout = pageLayoutTwoColumnRight;
      if (obj.isName("TwoPageLeft"))
        pageLayout = pageLayoutTwoPageLeft;
      if (obj.isName("TwoPageRight"))
        pageLayout = pageLayoutTwoPageRight;
    }
    obj.free();
    catDict.free();
  }
  return pageLayout;
}

NameTree::NameTree()
{
  size = 0;
  length = 0;
  entries = NULL;
}

NameTree::~NameTree()
{
  int i;

  for (i = 0; i < length; i++)
    delete entries[i];

  gfree(entries);
}

NameTree::Entry::Entry(Array *array, int index) {
    if (!array->getString(index, &name) || !array->getNF(index + 1, &value)) {
      Object aux;
      array->get(index, &aux);
      if (aux.isString() && array->getNF(index + 1, &value) )
      {
        name.append(aux.getString());
      }
      else
        error(errSyntaxError, -1, "Invalid page tree");
    }
}

NameTree::Entry::~Entry() {
  value.free();
}

void NameTree::addEntry(Entry *entry)
{
  if (length == size) {
    if (length == 0) {
      size = 8;
    } else {
      size *= 2;
    }
    entries = (Entry **) grealloc (entries, sizeof (Entry *) * size);
  }

  entries[length] = entry;
  ++length;
}

void NameTree::init(XRef *xrefA, Object *tree) {
  xref = xrefA;
  parse(tree);
}

void NameTree::parse(Object *tree) {
  Object names;
  Object kids, kid;
  int i;

  if (!tree->isDict())
    return;

  // leaf node
  if (tree->dictLookup("Names", &names)->isArray()) {
    for (i = 0; i < names.arrayGetLength(); i += 2) {
      NameTree::Entry *entry;

      entry = new Entry(names.getArray(), i);
      addEntry(entry);
    }
  }
  names.free();

  // root or intermediate node
  if (tree->dictLookup("Kids", &kids)->isArray()) {
    for (i = 0; i < kids.arrayGetLength(); ++i) {
      if (kids.arrayGet(i, &kid)->isDict())
	parse(&kid);
      kid.free();
    }
  }
  kids.free();
}

int NameTree::Entry::cmp(const void *voidKey, const void *voidEntry)
{
  GooString *key = (GooString *) voidKey;
  Entry *entry = *(NameTree::Entry **) voidEntry;

  return key->cmp(&entry->name);
}

GBool NameTree::lookup(GooString *name, Object *obj)
{
  Entry **entry;

  entry = (Entry **) bsearch(name, entries,
			     length, sizeof(Entry *), Entry::cmp);
  if (entry != NULL) {
    (*entry)->value.fetch(xref, obj);
    return gTrue;
  } else {
    printf("failed to look up %s\n", name->getCString());
    obj->initNull();
    return gFalse;
  }
}

Object NameTree::getValue(int index)
{
  if (index < length) {
    return entries[index]->value;
  } else {
    return Object();
  }
}

GooString *NameTree::getName(int index)
{
    if (index < length) {
	return &entries[index]->name;
    } else {
	return NULL;
    }
}

GBool Catalog::labelToIndex(GooString *label, int *index)
{
  char *end;

  PageLabelInfo *pli = getPageLabelInfo();
  if (pli != NULL) {
    if (!pli->labelToIndex(label, index))
      return gFalse;
  } else {
    *index = strtol(label->getCString(), &end, 10) - 1;
    if (*end != '\0')
      return gFalse;
  }

  if (*index < 0 || *index >= getNumPages())
    return gFalse;

  return gTrue;
}

GBool Catalog::indexToLabel(int index, GooString *label)
{
  char buffer[32];

  if (index < 0 || index >= getNumPages())
    return gFalse;

  PageLabelInfo *pli = getPageLabelInfo();
  if (pli != NULL) {
    return pli->indexToLabel(index, label);
  } else {
    snprintf(buffer, sizeof (buffer), "%d", index + 1);
    label->append(buffer);	      
    return gTrue;
  }
}

int Catalog::getNumPages()
{
  if (numPages == -1)
  {
    Object catDict, pagesDict, obj;

    xref->getCatalog(&catDict);
    if (!catDict.isDict()) {
      error(errSyntaxError, -1, "Catalog object is wrong type ({0:s})", catDict.getTypeName());
      catDict.free();
      return 0;
    }
    catDict.dictLookup("Pages", &pagesDict);
    catDict.free();

    // This should really be isDict("Pages"), but I've seen at least one
    // PDF file where the /Type entry is missing.
    if (!pagesDict.isDict()) {
      error(errSyntaxError, -1, "Top-level pages object is wrong type ({0:s})",
          pagesDict.getTypeName());
      pagesDict.free();
      return 0;
    }

    pagesDict.dictLookup("Count", &obj);
    // some PDF files actually use real numbers here ("/Count 9.0")
    if (!obj.isNum()) {
      error(errSyntaxError, -1, "Page count in top-level pages object is wrong type ({0:s})",
         obj.getTypeName());
      numPages = 0;
    } else {
      numPages = (int)obj.getNum();
    }

    obj.free();
    pagesDict.free();
  }

  return numPages;
}

PageLabelInfo *Catalog::getPageLabelInfo()
{
  if (!pageLabelInfo) {
    Object catDict;
    Object obj;

    xref->getCatalog(&catDict);
    if (!catDict.isDict()) {
      error(errSyntaxError, -1, "Catalog object is wrong type ({0:s})", catDict.getTypeName());
      catDict.free();
      return NULL;
    }

    if (catDict.dictLookup("PageLabels", &obj)->isDict()) {
      pageLabelInfo = new PageLabelInfo(&obj, getNumPages());
    }
    obj.free();
    catDict.free();
  }

  return pageLabelInfo;
}

Object *Catalog::getStructTreeRoot()
{
  if (structTreeRoot.isNone())
  {
     Object catDict;

     xref->getCatalog(&catDict);
     if (catDict.isDict()) {
       catDict.dictLookup("StructTreeRoot", &structTreeRoot);
     } else {
       error(errSyntaxError, -1, "Catalog object is wrong type ({0:s})", catDict.getTypeName());
       structTreeRoot.initNull();
     }
     catDict.free();
  }

  return &structTreeRoot;
}

Object *Catalog::getOutline()
{
  if (outline.isNone())
  {
     Object catDict;

     xref->getCatalog(&catDict);
     if (catDict.isDict()) {
       catDict.dictLookup("Outlines", &outline);
     } else {
       error(errSyntaxError, -1, "Catalog object is wrong type ({0:s})", catDict.getTypeName());
       outline.initNull();
     }
     catDict.free();
  }

  return &outline;
}

Object *Catalog::getDests()
{
  if (dests.isNone())
  {
     Object catDict;

     xref->getCatalog(&catDict);
     if (catDict.isDict()) {
       catDict.dictLookup("Dests", &dests);
     } else {
       error(errSyntaxError, -1, "Catalog object is wrong type ({0:s})", catDict.getTypeName());
       dests.initNull();
     }
     catDict.free();
  }

  return &dests;
}

Form *Catalog::getForm()
{
  if (!form) {
    if (acroForm.isDict()) {
      form = new Form(doc, &acroForm);
      // perform form-related loading after all widgets have been loaded
      form->postWidgetsLoad();
    }
  }

  return form;
}

ViewerPreferences *Catalog::getViewerPreferences()
{
  if (!viewerPrefs) {
    if (viewerPreferences.isDict()) {
      viewerPrefs = new ViewerPreferences(viewerPreferences.getDict());
    }
  }

  return viewerPrefs;
}

Object *Catalog::getNames()
{
  if (names.isNone())
  {
     Object catDict;

     xref->getCatalog(&catDict);
     if (catDict.isDict()) {
       catDict.dictLookup("Names", &names);
     } else {
       error(errSyntaxError, -1, "Catalog object is wrong type ({0:s})", catDict.getTypeName());
       names.initNull();
     }
     catDict.free();
  }

  return &names;
}

bool Catalog::getUS3Dict()
{
	Object perms_dict;
	catDict.dictLookup("Perms", &perms_dict);

	if (perms_dict.isDict())
	{
		Object ur3;	
		perms_dict.dictLookup("UR3", &ur3);

		return !ur3.isNull();
	}
	else
		return gFalse;
}

NameTree *Catalog::getDestNameTree()
{
  if (!destNameTree) {

    destNameTree = new NameTree();

    if (getNames()->isDict()) {
       Object obj;

       getNames()->dictLookup("Dests", &obj);
       destNameTree->init(xref, &obj);
       obj.free();
    }

  }

  return destNameTree;
}

NameTree *Catalog::getEmbeddedFileNameTree()
{
  if (!embeddedFileNameTree) {

    embeddedFileNameTree = new NameTree();

    if (getNames()->isDict()) {
       Object obj;

       getNames()->dictLookup("EmbeddedFiles", &obj);
       embeddedFileNameTree->init(xref, &obj);
       obj.free();
    }

  }

  return embeddedFileNameTree;
}

NameTree *Catalog::getJSNameTree()
{
  if (!jsNameTree) {

    jsNameTree = new NameTree();

    if (getNames()->isDict()) {
       Object obj;

       getNames()->dictLookup("JavaScript", &obj);
       jsNameTree->init(xref, &obj);
       obj.free();
    }

  }

  return jsNameTree;
}

