//
//  WVTConfig.h
//  WorldviewTribute
//
//  Created by Steve Gifford on 4/23/16.
//  Copyright © 2016 mousebird consulting. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WhirlyGlobeComponent.h>

@class WVTConfig;
@class WVTMatrixSet;

// All the various config objects are derived from dictionaries
@interface WVTObject : NSObject

@property WVTConfig *config;
@property NSDictionary *dict;

@end

/// A layer is a pointer to a single data layer
@interface WVTLayer : WVTObject

@property (readonly) NSString *name;
/// Set if this is one of the base layers.  Off for overlays.
@property (readonly) bool baseLayer;

/// Builds an object we can use to page with
- (MaplyRemoteTileSource *)buildTileSource;

@end

/// Data sources are a combination of the base URL and associated WMS and WMTS information
@interface WVTSource : WVTObject

@property (readonly) NSString *name;
@property (readonly) NSString *url;

// Return a matrix set by name
- (WVTMatrixSet *)findMatrixSet:(NSString *)name;

@end

/// MatrixSet describes how to access parts of a source
@interface WVTMatrixSet : WVTObject

@property (readonly) NSString *name;
@property (readonly) int maxZoom;
@property (readonly) int pixelsPerTile;

@end

/** WorldView-Tribute Config file.
    This is the WorldView config JSON as harvested from the NASA site.
  */
@interface WVTConfig : NSObject

// Load from JSON in the bundle
- (id)initWithFile:(NSString *)fname;

// Look up a layer by its name (rather than id)
- (WVTLayer *)findLayer:(NSString *)name;

// Look up a source by its name
- (WVTSource *)findSource:(NSString *)name;

@end