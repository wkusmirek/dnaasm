var docGeneration = angular.module('docGeneration');

docGeneration.directive(
    "shortReadsAssemblyLayout",
    function() {

        // Return the directive configuration.
        return({
            controller: "assemblingController",
            link: link,
            restrict: "A",
            templateUrl: appendVersion("views/short_reads_assembling.html")
        });

        // JS evenets can be bound to scope here
        function link( scope, element, attributes ) {
        }

    }
);