#include <stdio.h>
#include <stdlib.h>

#define RXML_TEST
#include <formats/rxml.h>

#include "libretrodb.h"


static void xml_converter_exit(int rc)
{
   fflush(stdout);
   exit(rc);
}

static void print_siblings(struct rxml_node *node, unsigned level)
{
   fprintf(stderr, "\n%*sName: %s\n", level * 4, "", node->name);
   if (node->data)
      fprintf(stderr, "%*sData: %s\n", level * 4, "", node->data);

   for (const struct rxml_attrib_node *attrib = 
         node->attrib; attrib; attrib = attrib->next)
      fprintf(stderr, "%*s  Attrib: %s = %s\n", level * 4, "",
            attrib->attrib, attrib->value);

   if (node->children)
      print_siblings(node->children, level + 1);

   if (node->next)
      print_siblings(node->next, level);
}

static void rxml_log_document(const char *path)
{
   rxml_document_t *doc = rxml_load_document(path);
   if (!doc)
   {
      fprintf(stderr, "rxml: Failed to load document: %s\n", path);
      return;
   }

   print_siblings(rxml_root_node(doc), 0);
   rxml_free_document(doc);
}

int main(int argc, char** argv)
{
	const char* xml_path;
	if (argc < 2)
	{
	  printf("usage:\n%s <db file> [args ...]\n", *argv);
	  xml_converter_exit(1);
	}
	argc--;
	argv++;
	
	xml_path  = *argv;
	argc--;
	argv++;	

	rxml_log_document(xml_path);

	return 0;
}