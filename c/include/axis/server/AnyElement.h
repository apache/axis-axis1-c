#if !defined(__ANYELEMENT_H__INCLUDED_)
#define __ANYELEMENT_H__INCLUDED_

#define MAX_NO_OF_ATTRIBUTES 100

typedef enum { START_ELEMENT=0, CHARACTER_ELEMENT, END_ELEMENT, START_PREFIX, END_PREFIX} XML_NODE_TYPE;

typedef struct {
	XML_NODE_TYPE m_type;
	const char* m_pchNameOrValue;
	const char* m_pchNamespace;
	/* each attribute has 3 entities: localname, namespace, value in order */
	const char* m_pchAttributes[MAX_NO_OF_ATTRIBUTES*3]; 
} AnyElement;

#endif
