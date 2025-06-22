//
//  zaniaFilterApp.swift
//  zaniaFilter
//
//  Created by Colby Janecka on 6/22/25.
//

import SwiftUI

@main
struct zaniaFilterApp: App {
    @State private var hostModel = AudioUnitHostModel()

    var body: some Scene {
        WindowGroup {
            ContentView(hostModel: hostModel)
        }
    }
}
