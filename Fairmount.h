
#import <Cocoa/Cocoa.h>
#import <DiskArbitration/DiskArbitration.h>

#include "Types.h"
#include "HTTPServer.h"

//-------------------------------------------------------------------------
@interface DVDServer : NSObject
{
    DASessionRef    mDASession;
    DADiskRef       mOriginalDisk;
    DADiskRef       mDecryptedDisk;
    HTTPServer      *mHTTPServer;
    BOOL            mRequestingService, mCallbackCalled;
    NSString        *mStatus;
    NSTableView     *mTableView;
    NSURL           *mExtractDir;
    int             mErrCode;
    NSObject        *mCaller;
}
- (id) initWithSession:(DASessionRef)session tableView:(NSTableView*)tableView extractDir:(NSURL*)extractDir caller:(NSObject*)caller;

- (void) requestDone:(int)errCode;
- (DADiskRef) decryptedDisk;
- (NSString *) volumeName;
- (NSString *) status;
- (void) setStatus:(NSString*)status;
- (int64) bytesRead;
- (int64) badSectorCount;


- (void) takeOverDisk:(DADiskRef)disk;

// returns true on success
- (BOOL) stopServingAndEject:(BOOL)eject;
@end

//-------------------------------------------------------------------------
@interface Fairmount : NSObject
{
    IBOutlet NSTableView    *mTableView;

    NSMutableArray          *mServers;
    DASessionRef            mDASession;
    IBOutlet NSWindow       *mVLCWindow;
    NSURL                  *mExtractDir;
}

- (void) downloadVLC:(id)sender;
- (void) retryVLC:(id)sender;
- (void) removeServer:(DVDServer*)server;

- (void) diskAppearedCb:(DADiskRef)disk;
- (void) diskDisappearedCb:(DADiskRef)disk;

- (void) takeOver:(DADiskRef)disk;

- (void) autoReloadTableView;
@end
