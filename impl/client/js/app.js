/// @file app.js
/// @brief main client module, AngularJS application with routing

var myapp = angular.module('myApp', ['ngRoute', 'ngDialog', 'pascalprecht.translate', 'myAppControllers', 'myAppServices'] )
	.config(['$routeProvider', '$translateProvider',
			function($routeProvider, $translateProvider) {
				$routeProvider.when('/assembling', {
					templateUrl: 'views/assembling.html',
				});
				$routeProvider.when('/settings', {
					templateUrl: 'views/settings.html',
				});
				$routeProvider.when('/help', {
					templateUrl: 'views/help.html',
				});
				$routeProvider.when('/users', {
					templateUrl: 'views/users.html',
				});
				$routeProvider.when('/start_page', {
					templateUrl: 'views/start_page.html',
				});
				$routeProvider.when('/file_formats', {
					templateUrl: 'views/file_formats.html',
				});
				$routeProvider.when('/algorithms', {
					templateUrl: 'views/algorithms.html',
				});
				$routeProvider.when('/files', {
					templateUrl: 'views/files.html',
				});
				$routeProvider.when('/all_files', {
					templateUrl: 'views/all_files.html',
				});
				$routeProvider.when('/all_jobs', {
					templateUrl: 'views/all_jobs.html',
				});
				$routeProvider.when('/alignment', {
					templateUrl: 'views/alignment.html',
				});
				$routeProvider.when('/scaffolding', {
					templateUrl: 'views/scaffolding.html',
				});
				$routeProvider.otherwise( {
					redirectTo: '/assembling'
				});
				$translateProvider.useStaticFilesLoader({
					prefix: 'lang/',
					suffix: '.json' });
				$translateProvider.preferredLanguage('en');
			}]);

