#include "snmp.h"

#include "exceptions.h"
#include "primitives/macaddr.h"

SNMP SNMP::instance = SNMP();

SNMP::SNMP() {
}

SNMP::~SNMP() {
	snmp_close(this->ss);
}

SNMP& SNMP::getInstance() {
	return SNMP::instance;
}

void SNMP::init(const char* server, const char* community) {
	struct snmp_session session;
	snmp_sess_init(&session);

	session.peername	= const_cast<char*>(server);
	session.version		= SNMP_VERSION_2c;
	session.community	= (u_char*)community;
	session.community_len	= strlen(community);

	this->ss = snmp_open(&session);
}


macaddr_t SNMP::getFirstMac(const oid* objid, size_t objid_len) {
	macaddr_t ret;
	bool found = false;

	struct snmp_pdu* pdu;
	pdu = snmp_pdu_create(SNMP_MSG_GET);
	snmp_add_null_var(pdu, objid, objid_len);

	struct snmp_pdu* response;
	snmp_synch_response(this->ss, pdu, &response);

	struct variable_list* vars;
	for (vars = response->variables; vars && !found; vars = vars->next_variable) {
		if (vars->type == ASN_OCTET_STR && vars->val_len == 6) {
			ret = macaddr_fsstr(vars->val.string, vars->val_len);
			found = true;
		}
	}
	
	snmp_free_pdu(response);

	if (!found)
		throw SNMPNotFound();

	return ret;
}

long int SNMP::getFirstInteger(const oid* objid, size_t objid_len) {
	long int ret;
	bool found = false;

	struct snmp_pdu* pdu;
	pdu = snmp_pdu_create(SNMP_MSG_GET);
	snmp_add_null_var(pdu, objid, objid_len);

	struct snmp_pdu* response;
	snmp_synch_response(this->ss, pdu, &response);

	struct variable_list* vars;
	for (vars = response->variables; vars && !found; vars = vars->next_variable) {
		if (vars->type == ASN_INTEGER) {
			ret = *(vars->val.integer);
			found = true;
		}
	}
	
	snmp_free_pdu(response);

	if (!found)
		throw SNMPNotFound();

	return ret;
}

//TODO
void SNMP::getNextOID(const oid* objid, size_t objid_len) {
	struct snmp_pdu* pdu;
	pdu = snmp_pdu_create(SNMP_MSG_GETNEXT);
	snmp_add_null_var(pdu, objid, objid_len);

	struct snmp_pdu* response;
	snmp_synch_response(this->ss, pdu, &response);

	struct variable_list* vars;
	for (vars = response->variables; vars; vars = vars->next_variable) {
		print_variable(vars->name, vars->name_length, vars);
	}
	
	snmp_free_pdu(response);
}
