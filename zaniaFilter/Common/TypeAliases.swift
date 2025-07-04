//
//  TypeAliases.swift
//  zaniaFilter
//
//  Created by Colby Janecka on 6/22/25.
//

import CoreMIDI
import AudioToolbox

#if os(iOS) || os(visionOS)
import UIKit

public typealias ViewController = UIViewController
#elseif os(macOS)
import AppKit

public typealias KitView = NSView
public typealias ViewController = NSViewController
#endif
