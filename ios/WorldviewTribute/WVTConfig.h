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
@class WVTDisplayCard;

// All the various config objects are derived from dictionaries
@interface WVTObject : NSObject

@property WVTConfig *config;
@property NSDictionary *dict;

@end

/// A layer is a pointer to a single data layer
@interface WVTLayer : WVTObject

@property (readonly) NSString *name;
@property (readonly) NSString *title;
@property (readonly) NSString *subtitle;
/// Set if this is one of the base layers.  Off for overlays.
@property (readonly) bool baseLayer;
/// Set from the layerOrder
@property (assign) int drawPriority;
/// Set by the layer manager if this is currently being displayed
@property (assign) bool isDisplayed;
/// Set if the layer is even in the layer list
@property (assign) bool isActive;

/// Builds an object we can use to page with
- (MaplyRemoteTileSource *)buildTileSource:(NSString *)dateString;

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

// A measurement source is a group of settings (layers)
@interface WVTMeasurementSource : WVTObject

@property (readonly) NSString *name;
@property (readonly) NSString *title;
@property NSArray *layers;

@end

/// A measurement is a group of sources
@interface WVTMeasurement: WVTObject

@property (readonly) NSString *name;
@property (readonly) NSString *title;
@property (readonly) NSString *subTitle;
// The MVTLayer objects associated with this measurement
@property NSArray *sources;

@end

/// A card is a list of measurements that are associated with a given type of interest (e.g. Air Quality)
@interface WVTCard : WVTObject

@property (readonly) NSString *name;
@property (readonly) NSString *title;
@property (readonly) NSString *imageName;
@property NSArray *measurements;

// Return all the layers for this card
- (NSArray *)allLayers;

// Build a displayable version of the card with sources and layers flattened
- (WVTDisplayCard *)makeDisplayCard;

@end

// Display version of measurement objects
@interface WVTDisplayMeasurement : NSObject

// Original measurement
@property (readonly) WVTMeasurement *measure;

// Sources interleaved with their layers
@property NSArray *sourcesAndLayers;

@end

@interface WVTDisplayCard : NSObject

// Original card
@property (readonly) WVTCard *card;

// Display version of measurements
@property NSArray *displayMeasures;

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

// Look up a measurement by its name
- (WVTMeasurement *)findMeasurement:(NSString *)name;

// Look up all the cards for a given category
- (NSArray *)findCardsForCategory:(NSString *)category;

// Return the number of categories
- (NSUInteger)getNumCategories;

// Return the Nth category
- (NSArray *)cardsForNthCategory:(int)catID;

@end
