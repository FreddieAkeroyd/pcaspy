#ifndef PV_H
#define PV_H

#include <casdef.h>
#include <gddAppFuncTable.h>

class PV; 

class AsyncWriteIO : public casAsyncWriteIO {
    public:
        AsyncWriteIO(const casCtx & ctxIn,  PV & pvIn); 
        ~AsyncWriteIO();
    private:
        PV & pv; 
}; 

class PV : public casPV {
    public:
        PV();
        virtual ~PV();

        virtual caStatus read ( const casCtx & ctx, gdd & protoIn);

        virtual caStatus getValue(gdd &value) { return S_casApp_success; };
        virtual caStatus getPrecision(gdd &prec) {return S_casApp_success;};
        virtual caStatus getHighLimit(gdd &hilim) {return S_casApp_success;};
        virtual caStatus getLowLimit(gdd &lolim) {return S_casApp_success;};
        virtual caStatus getUnits(gdd &units) {return S_casApp_success;};
        virtual caStatus getEnums(gdd &enums) {return S_casApp_success;};

        caStatus postEvent(gdd &value);
        void destroy();

        void startAsyncWrite(const casCtx & ctx); 
        void endAsyncWrite(caStatus status); 
        void removeAsyncWrite(); 

        virtual bool readAccess(const char * const pUserName,  const char * const pHostName)  const { return true; }
        virtual bool writeAccess(const char * const pUserName,  const char * const pHostName) const { return true; }
        casChannel * createChannel ( const casCtx &ctx, const char * const pUserName, const char * const pHostName); 
    
        static void initFT();
    private:
        AsyncWriteIO * pAsyncWrite; 
        static gddAppFuncTable<PV> ft;
        static int initialized;
};

#endif
