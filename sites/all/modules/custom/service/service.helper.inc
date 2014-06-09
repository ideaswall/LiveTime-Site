<?php

/**
 * @file
 * Reource functions for services api of LiveTime.
 */

function service_response_header() {

	// Set response header type to json
	header('Content-Type: application/json');
}