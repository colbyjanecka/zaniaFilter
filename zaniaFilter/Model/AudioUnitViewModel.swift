//
//  AudioUnitViewModel.swift
//  zaniaFilter
//
//  Created by Colby Janecka on 6/22/25.
//

import SwiftUI
import AudioToolbox
internal import CoreAudioKit

struct AudioUnitViewModel {
    var showAudioControls: Bool = false
    var showMIDIContols: Bool = false
    var title: String = "-"
    var message: String = "No Audio Unit loaded.."
    var viewController: ViewController?
}
