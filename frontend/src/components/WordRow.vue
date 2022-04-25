<script setup>
import Letter from '@/components/Letter.vue';
import {defineProps, ref, watch} from "vue"

// la méthode de construire en fonction de la taille de la solution me semble vraiment pas opti cela induit une sorte de ralentissement chiant
const rowprop = defineProps({
    solution: String,
    word: String,
    submitted: Boolean,
})

// storage de la couleur de chacune des lignes

let b = new Array(rowprop.solution.length);
const colortab = ref(b);

/*
Ceci est un watcher il va permettre de surveiller les changements d'une variable et d'appeler une fonction lorsqu'elle change

En particulier ici on vérifie si la ligne est "validée" par l'utilisateur et peut être traité par l'algorithme

Ici le traitement se fait en frontend mais il faudrait peut être faire un traitement en backend
*/

watch( () => rowprop.submitted, (newVal) => {
    if (newVal) {
        let guess = rowprop.word;
        let solution = rowprop.solution;
        let letterbag = [];

        for (let i = 0; i < solution.length; i++) {
            // on vérifie si la lettre est bien placée
            if (guess[i] == solution[i]) {
                colortab.value[i] = "#cc0808";
            } else {
                // on met la lettre dans notre sac car elle peut être mal placée
                letterbag.push(solution[i]);
                // on initialise à gris la case
                colortab.value[i] = "#1e1e1e";
                }
            }
        for (let i=0; i < solution.length; i++) {
            if (colortab.value[i] == "#1e1e1e") {
                if (letterbag.includes(guess[i])) {
                    colortab.value[i] = "#bd8517";
                    letterbag.splice(letterbag.indexOf(guess[i]), 1);
                    }
                }
            }
        }
});



</script>

<template>
    <b-container>
        <b-row class="justify-content-center">
            <letter v-for="i in rowprop.solution.length" :key="i" :letter=word[i-1] :color=colortab[i-1]></letter>
        </b-row>
    </b-container>
</template>


<style scoped>
</style>