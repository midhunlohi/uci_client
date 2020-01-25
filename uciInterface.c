#include <uci.h>
#include "uciInterface.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int configDelete(char *path){

   struct  uci_ptr ptr;
   struct  uci_context *c = NULL;
   c = uci_alloc_context();

	if(!c){
		goto error;
	}

   if ((uci_lookup_ptr(c, &ptr, path, true) != UCI_OK))
   {
	 printf("uci look up failed\n");
	 uci_free_context(c);
	 goto error;
   }

   if(uci_delete(c, &ptr)){
	   goto error;
   }

	if (uci_commit(c, &ptr.p, false)){
	   goto error;
	}

   uci_free_context(c);
   return 0;
error:
   return -1;

}

int configGet(char *path, char *data ){

   struct  uci_ptr ptr;
   struct  uci_context *c = NULL;
   c = uci_alloc_context();

	if(!c){
		goto error;
	}

   if ((uci_lookup_ptr(c, &ptr, path, true) != UCI_OK) ||
		   (ptr.o==NULL || ptr.o->v.string==NULL))
   {
	 printf("uci look up failed\n");
	 uci_free_context(c);
	 goto error;
   }

   if(ptr.flags & UCI_LOOKUP_COMPLETE){
		  strcpy(data, ptr.o->v.string);
   }

   uci_free_context(c);
   return 0;
error:
   return -1;

}

int configSet(char *path, char *data ){

   struct  uci_ptr ptr;
   struct  uci_context *c = NULL;
   c = uci_alloc_context();

	if(!c){
		goto error;
	}

   if ((uci_lookup_ptr(c, &ptr, path, true) != UCI_OK))
   {
	 printf("uci look up failed\n");
	 uci_free_context(c);
	 goto error;
   }

	ptr.value = data ;

	if (uci_set(c, &ptr)){
	   goto error;
	}
	if (uci_commit(c, &ptr.p, false)){
	   goto error;
	}

   uci_free_context(c);
   return 0;
error:
   return -1;

}

int uciAddNewSection(char *path){

	struct uci_ptr ptr;
	struct uci_context *ctx = uci_alloc_context();

	if(!ctx){
		printf("uci context allocation failed\n");
		goto error;
	}

	if (uci_lookup_ptr(ctx, &ptr, path, true) != UCI_OK) {
		goto error;
	}

	if (uci_set(ctx, &ptr)){
		goto error;
	}

	if (uci_commit(ctx, &ptr.p, false)){
		goto error;
	}

	uci_free_context(ctx);
	return 0;

error:
   return -1;
}


